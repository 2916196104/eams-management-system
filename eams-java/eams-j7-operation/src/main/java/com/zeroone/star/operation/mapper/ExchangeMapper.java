package com.zeroone.star.operation.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.operation.entity.CreditExchange;
import com.zeroone.star.project.dto.j7.operation.ExchangeDTO;
import com.zeroone.star.project.query.j7.operation.ExchangeQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * 积分兑换Mapper接口
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-22
 */
@Mapper
public interface ExchangeMapper extends BaseMapper<CreditExchange> {
    
    /**
     * 分页查询兑换申请列表
     */
    List<ExchangeDTO> selectExchangePage(@Param("query") ExchangeQuery query);
    
    /**
     * 统计兑换申请总数
     */
    long countExchange(@Param("query") ExchangeQuery query);
    
    /**
     * 审核兑换申请
     */
    int updateExchangeVerify(@Param("dto") ExchangeDTO dto);
}
