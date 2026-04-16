package com.zeroone.star.operation.service.impl;

import com.zeroone.star.operation.mapper.ExchangeMapper;
import com.zeroone.star.operation.service.ExchangeService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.ExchangeDTO;
import com.zeroone.star.project.query.j7.operation.ExchangeQuery;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 积分兑换服务实现类
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-22
 */
@Service
@RequiredArgsConstructor
public class ExchangeServiceImpl implements ExchangeService {

    /**
     * 积分兑换Mapper
     */
    private final ExchangeMapper exchangeMapper;
/*
 * 获取兑换申请列表
 * */
    @Override
    public PageDTO<ExchangeDTO> queryPage(ExchangeQuery query) {
        List<ExchangeDTO> list = exchangeMapper.selectExchangePage(query);
        long total = exchangeMapper.countExchange(query);
        // 构建分页结果
        PageDTO<ExchangeDTO> result = new PageDTO<>();
        // 设置总记录数
        result.setTotal(total);
        // 设置分页数据
        result.setRows(list);
        return result;
    }
/*
 * 审核兑换申请
 * */
    @Override
    public boolean approveExchange(ExchangeDTO exchangeDTO) {
        return exchangeMapper.updateExchangeVerify(exchangeDTO) > 0;
    }
}
