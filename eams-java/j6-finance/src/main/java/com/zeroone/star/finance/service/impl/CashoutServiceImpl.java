package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.finance.entity.Cashout;
import com.zeroone.star.finance.mapper.CashoutMapper;
import com.zeroone.star.finance.service.ICashoutService;
import com.zeroone.star.project.dto.j6.finance.CashoutAddDTO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;

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
}
