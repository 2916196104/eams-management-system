package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.finance.entity.Cashout;
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

@Service
public class CashoutServiceImpl extends ServiceImpl<CashoutMapper, CashoutDO> implements ICashoutService {
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
}
