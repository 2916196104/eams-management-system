package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.finance.mapper.CashoutMapper;
import com.zeroone.star.finance.service.ICashoutService;
import com.zeroone.star.project.dataobject.j6.finance.CashoutDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.CashoutAddDTO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;

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
}
