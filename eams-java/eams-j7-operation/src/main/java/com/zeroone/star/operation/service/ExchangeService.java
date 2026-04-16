package com.zeroone.star.operation.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.ExchangeDTO;
import com.zeroone.star.project.query.j7.operation.ExchangeQuery;

/**
 * <p>
 * 积分兑换服务接口
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-22
 */
public interface ExchangeService {
    /**
     * 获取兑换申请列表
     * @param condition 查询条件
     * @return 兑换申请列表
     */
    PageDTO<ExchangeDTO> queryPage(ExchangeQuery condition);

    /**
     * 审核兑换申请
     * @param exchangeDTO 审核信息
     * @return 审核结果
     */
    boolean approveExchange(ExchangeDTO exchangeDTO);
}
