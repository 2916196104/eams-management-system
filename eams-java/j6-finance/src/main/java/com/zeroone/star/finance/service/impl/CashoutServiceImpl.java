package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.finance.mapper.CashoutMapper;
import com.zeroone.star.finance.service.ICashoutService;
import com.zeroone.star.project.dataobject.j6.finance.CashoutDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.BatchVerifyDTO;
import com.zeroone.star.project.dto.j6.finance.CashoutAddDTO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.List;

/**
 * 请款服务实现类
 */
@Service
public class CashoutServiceImpl extends ServiceImpl<CashoutMapper, CashoutDO> implements ICashoutService {

    /**
     * 审批状态：待审核
     */
    private static final int VERIFY_STATE_PENDING = 0;

    /**
     * 审批状态：审核通过
     */
    private static final int VERIFY_STATE_APPROVED = 1;

    /**
     * 审批状态：已驳回
     */
    private static final int VERIFY_STATE_REJECTED = 2;

    /**
     * 审批状态：已作废
     */
    private static final int VERIFY_STATE_CANCELLED = 3;

    /**
     * 请款列表查询（条件+分页）
     */
    @Override
    public PageDTO<CashoutListVO> queryCashoutPage(CashoutListQuery query) {
        Page<CashoutListVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        baseMapper.selectCashoutPage(page, query);
        return PageDTO.create(page);
    }

    /**
     * 请款信息详情查询
     */
    @Override
    public CashoutDetailVO getCashoutDetail(Long id) {
        return baseMapper.selectCashoutDetailById(id);
    }

    /**
     * 保存请款申请
     */
    @Override
    public Long saveCashout(CashoutAddDTO cashoutAddDTO) {
        CashoutDO cashoutDO = new CashoutDO();
        cashoutDO.setTitle(cashoutAddDTO.getTitle());
        cashoutDO.setType(cashoutAddDTO.getType());
        cashoutDO.setAmount(cashoutAddDTO.getAmount());
        cashoutDO.setPayeeName(cashoutAddDTO.getPayeeName());
        cashoutDO.setAccount(cashoutAddDTO.getAccount());
        cashoutDO.setInfo(cashoutAddDTO.getInfo());
        cashoutDO.setAttachFile(cashoutAddDTO.getAttachFile());
        cashoutDO.setVerifyState(VERIFY_STATE_PENDING);
        cashoutDO.setAddTime(LocalDateTime.now());
        // TODO: 从当前登录用户获取 creator 和 orgId
        cashoutDO.setCreator(1L);
        cashoutDO.setOrgId(1L);
        this.save(cashoutDO);
        return cashoutDO.getId();
    }

    /**
     * 作废请款申请
     */
    @Override
    public void cancelCashout(Long id) {
        CashoutDO cashout = this.getById(id);
        if (cashout == null) {
            throw new RuntimeException("请款记录不存在");
        }
        if (cashout.getVerifyState() != VERIFY_STATE_PENDING) {
            throw new RuntimeException("只能作废待审核状态的申请");
        }
        cashout.setVerifyState(VERIFY_STATE_CANCELLED);
        // TODO: 从当前登录用户获取 editor
        cashout.setEditor(1L);
        cashout.setEditTime(LocalDateTime.now());
        this.updateById(cashout);
    }

    /**
     * 批量审核请款（通过/驳回）
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public void batchVerify(BatchVerifyDTO dto) {
        List<Long> ids = dto.getIds();
        Integer targetState = dto.getVerifyState();

        // 1. 基础参数校验
        if (ids == null || ids.isEmpty()) {
            throw new IllegalArgumentException("请选择至少一条请款记录");
        }
        if (targetState == null) {
            throw new IllegalArgumentException("审核状态不能为空");
        }
        // 校验目标状态是否合法（只允许通过或驳回）
        if (targetState != VERIFY_STATE_APPROVED && targetState != VERIFY_STATE_REJECTED) {
            throw new IllegalArgumentException("审核状态只能是：通过(1)、驳回(2)");
        }
        // 校验驳回时的备注必填
        if (targetState == VERIFY_STATE_REJECTED &&
                (dto.getVerifyRemark() == null || dto.getVerifyRemark().trim().isEmpty())) {
            throw new IllegalArgumentException("驳回请款时必须填写备注");
        }

        // 2. 前置校验：查询待审核的记录数量
        LambdaQueryWrapper<CashoutDO> checkWrapper = new LambdaQueryWrapper<>();
        checkWrapper.in(CashoutDO::getId, ids)
                .eq(CashoutDO::getVerifyState, VERIFY_STATE_PENDING);
        long pendingCount = this.count(checkWrapper);

        // 如果没有待审核的记录，直接抛出异常
        if (pendingCount == 0) {
            throw new RuntimeException("所选记录中无待审核的请款单，无法执行审核操作");
        }
        // 如果部分记录已审核，提示用户
        if (pendingCount < ids.size()) {
            throw new RuntimeException(String.format(
                    "所选%d条记录中，有%d条已审核，仅%d条待审核，审核操作已终止",
                    ids.size(), ids.size() - pendingCount, pendingCount));
        }

        // 3. 批量更新：仅更新待审核的记录
        LambdaUpdateWrapper<CashoutDO> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.in(CashoutDO::getId, ids)
                .eq(CashoutDO::getVerifyState, VERIFY_STATE_PENDING)
                .set(CashoutDO::getVerifyState, targetState)
                .set(CashoutDO::getVerifyTime, LocalDateTime.now())
                .set(CashoutDO::getVerifyRemark, dto.getVerifyRemark());
        // TODO: 从当前登录用户获取审核人ID
        // .set(CashoutDO::getVerifyStaff, currentUserId)

        // 执行更新
        boolean success = this.update(updateWrapper);
        if (!success) {
            throw new RuntimeException("审核操作执行失败");
        }
    }
}
