package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.finance.entity.Cashout;
import com.zeroone.star.finance.mapper.CashoutMapper;
import com.zeroone.star.finance.service.ICashoutService;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j6.finance.BatchVerifyDTO;
import com.zeroone.star.project.dto.j6.finance.CashoutAddDTO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.List;

@Service
public class CashoutServiceImpl extends ServiceImpl<CashoutMapper, Cashout> implements ICashoutService {

    public static final int VERIFY_STATE_PENDING = 0;
    public static final int VERIFY_STATE_APPROVED = 1;
    public static final int VERIFY_STATE_REJECTED = 2;
    public static final int VERIFY_STATE_CANCELLED = 3;

    public Long saveCashout(CashoutAddDTO addDTO) {
        Cashout cashout = new Cashout();
        cashout.setTitle(addDTO.getTitle());
        cashout.setType(addDTO.getType());
        cashout.setAmount(addDTO.getAmount());
        cashout.setPayeeName(addDTO.getPayeeName());
        cashout.setAccount(addDTO.getAccount());
        cashout.setInfo(addDTO.getInfo());
        cashout.setAttachFile(addDTO.getAttachFile());
        cashout.setVerifyState(VERIFY_STATE_PENDING);
        cashout.setAddTime(LocalDateTime.now());
        cashout.setCreator(1L);
        cashout.setOrgId(1L);
        this.save(cashout);
        return cashout.getId();
    }

    public Long cancelCashout(Long id) {
        Cashout cashout = this.getById(id);
        if (cashout == null) {
            throw new RuntimeException("请款记录不存在");
        }
        if (cashout.getVerifyState() != VERIFY_STATE_PENDING) {
            throw new RuntimeException("只能作废待审核状态的申请");
        }
        cashout.setVerifyState(VERIFY_STATE_CANCELLED);
        cashout.setEditor(1L);
        cashout.setEditTime(LocalDateTime.now());
        this.updateById(cashout);
        return id;
    }

    public Page<CashoutListVO> listCashouts(CashoutListQuery query) {
        Page<Cashout> page = new Page<>(query.getPageIndex(), query.getPageSize());
        QueryWrapper<Cashout> wrapper = new QueryWrapper<>();
        wrapper.eq("creator", 1L);
        wrapper.orderByDesc("add_time");
        Page<Cashout> result = this.page(page, wrapper);
        Page<CashoutListVO> voPage = new Page<>(result.getCurrent(), result.getSize(), result.getTotal());
        return voPage;
    }

    public CashoutDetailVO getCashoutDetail(Long id) {
        Cashout cashout = this.getById(id);
        if (cashout == null) {
            return null;
        }
        CashoutDetailVO vo = new CashoutDetailVO();
        vo.setId(cashout.getId());
        vo.setTitle(cashout.getTitle());
        vo.setType(cashout.getType());
        vo.setCreator(cashout.getCreator());
        vo.setPayeeName(cashout.getPayeeName());
        vo.setAccount(cashout.getAccount());
        vo.setAmount(cashout.getAmount());
        vo.setInfo(cashout.getInfo());
        vo.setVerifyState(cashout.getVerifyState());
        vo.setVerifyStaff(cashout.getVerifyStaff());
        vo.setVerifyTime(cashout.getVerifyTime());
        vo.setVerifyRemark(cashout.getVerifyRemark());
        vo.setApplyTime(cashout.getAddTime());
        vo.setAttachFile(cashout.getAttachFile());
        vo.setOrgId(cashout.getOrgId());
        return vo;
    }

    @Resource
    private CashoutMapper cashoutMapper;

    @Resource
    private UserHolder userHolder;
    /**
     * 批量审核请款（通过/驳回）
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public void batchVerify(BatchVerifyDTO dto) {
        List<Long> ids = dto.getIds();
        // 1. 基础参数校验
        if (ids == null || ids.isEmpty()) {
            throw new IllegalArgumentException("请选择至少一条请款记录");
        }
        if (dto.getVerifyState() == null) {
            throw new IllegalArgumentException("审核状态不能为空");
        }
        // 校验驳回时的备注
        if (dto.getVerifyState() == VERIFY_STATE_REJECTED &&
                (dto.getVerifyRemark() == null || dto.getVerifyRemark().trim().isEmpty())) {
            throw new IllegalArgumentException("驳回请款时必须填写备注");
        }
        // 校验目标状态是否合法
        if (!Arrays.asList(VERIFY_STATE_APPROVED, VERIFY_STATE_REJECTED, VERIFY_STATE_CANCELLED).contains(dto.getVerifyState())) {
            throw new IllegalArgumentException("审核状态只能是：通过(1)、驳回(2)、取消(3)");
        }

        // 2. 前置校验：查询待审核的记录数量，排除已审核的记录
        LambdaQueryWrapper<Cashout> checkWrapper = new LambdaQueryWrapper<>();
        checkWrapper.in(Cashout::getId, ids)
                .eq(Cashout::getVerifyState, VERIFY_STATE_PENDING); // 只查待审核的
        long pendingCount = cashoutMapper.selectCount(checkWrapper);

        // 如果没有待审核的记录，直接抛出异常
        if (pendingCount == 0) {
            throw new RuntimeException("所选记录中无待审核的请款单，无法执行审核操作");
        }
        // 如果部分记录已审核，提示用户
        if (pendingCount < ids.size()) {
            throw new RuntimeException(String.format("所选%d条记录中，有%d条已审核（通过/驳回/取消），仅%d条待审核，审核操作已终止",
                    ids.size(), ids.size() - pendingCount, pendingCount));
        }

        // 3. 从请求头获取当前登录用户信息
        /*
        UserDTO currentUser;
        try {
            currentUser = userHolder.getCurrentUser();
            if (currentUser == null) {
                throw new RuntimeException("未获取到登录用户信息，请先登录");
            }
        } catch (Exception e) {
            throw new RuntimeException("解析登录用户信息失败：" + e.getMessage());
        }
        Long verifyStaffId = Long.parseLong(currentUser.getId());
        */

        // 4. 批量更新：仅更新待审核的记录，避免重复操作
        LambdaUpdateWrapper<Cashout> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.in(Cashout::getId, ids)
                .eq(Cashout::getVerifyState, VERIFY_STATE_PENDING) // 核心：只更新待审核的记录
                .set(Cashout::getVerifyState, dto.getVerifyState()) // 设置最终审核状态
                //.set(Cashout::getVerifyStaff, verifyStaffId) // 审核人ID
                .set(Cashout::getVerifyTime, LocalDateTime.now())   // 审核时间
                .set(Cashout::getVerifyRemark, dto.getVerifyRemark()); // 审核备注

        // 执行更新并校验结果
        int updateCount = cashoutMapper.update(null, updateWrapper);
        if (updateCount == 0) {
            throw new RuntimeException("审核操作执行失败，未更新任何记录");
        }

    }



    /**
     * 适配Java 8的字符串空白判断（替代String.isBlank()）
     */
    private boolean isStringBlank(String str) {
        if (str == null) {
            return true;
        }
        for (int i = 0; i < str.length(); i++) {
            if (!Character.isWhitespace(str.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    /**
     * 判断BatchVerifyDTO是否为空白（核心字段全空）
     */
    private boolean isDTOBlank(BatchVerifyDTO dto) {
        if (dto == null) {
            return true;
        }
        return (dto.getIds() == null || dto.getIds().isEmpty())
                && dto.getVerifyState() == null
                && isStringBlank(dto.getVerifyRemark());
    }
}
