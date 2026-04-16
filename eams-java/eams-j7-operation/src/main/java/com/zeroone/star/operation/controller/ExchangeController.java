package com.zeroone.star.operation.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.ExchangeDTO;
import com.zeroone.star.project.j7.operation.ExchangeApi;
import com.zeroone.star.project.query.j7.operation.ExchangeQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * <p>
 * 描述：兑换控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 1
 * @version 1.0.0
 */

@RestController
@RequestMapping("/j7-operation/j7-exchange")
@Api(tags = "积分兑换管理")
public class ExchangeController implements ExchangeApi{
    /**
     * 获取兑换申请列表
     * @param condition 查询条件
     * @return 兑换申请列表
     * @author 1
     * @version 1.0.0
     * @date 2026-3-16
     */

    @GetMapping("/get-exchange-list")
    @ApiOperation("获取兑换申请列表")
    @Override
    public JsonVO<PageDTO<ExchangeDTO>> queryPage(ExchangeQuery condition) {
        return null;
    }

    /**
     * 审核申请
     * @param exchangeDTO 审核信息
     * @return 审核结果
     * @author 1
     * @version 1.0.0
     * @date 2026-3-16
     */

    @PostMapping("/apperove-exchange")
    @ApiOperation("审核兑换申请")
    @Override
    public JsonVO<Boolean> approveExchange(@RequestBody ExchangeDTO exchangeDTO) {
        return null;
    }

}