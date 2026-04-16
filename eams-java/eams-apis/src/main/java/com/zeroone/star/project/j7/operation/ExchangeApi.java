package com.zeroone.star.project.j7.operation;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.ExchangeDTO;
import com.zeroone.star.project.query.j7.operation.ExchangeQuery;
import com.zeroone.star.project.vo.JsonVO;

public interface ExchangeApi {
    /**
     * 查询积分兑换申请列表
     * @param condition 查询条件
     * @return 积分兑换申请列表
     * @author 1
     * @version 1.0.0
     * @date 2023-12-20
     */

    JsonVO<PageDTO<ExchangeDTO>> queryPage(ExchangeQuery condition);

    /**
     * 审核积分兑换申请
     * @param exchangeDTO 积分兑换申请信息
     * @return 审核结果
     * @author 1
     * @version 1.0.0
     * @date 2023-12-20
     */
     JsonVO<Boolean> approveExchange(ExchangeDTO exchangeDTO);

}
