package com.zeroone.star.finance.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.zeroone.star.project.dto.j6.finance.BatchVerifyDTO;
import com.zeroone.star.project.j6.finance.CashoutApi;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

/**
 * <p>
 * 请款审核管理控制器（实现API接口）
 * </p>
 * <p>版权: &copy;01星球</p>
 * <p>地址: 01星球总部</p>
 *
 * @author 你的名字
 * @version 1.0.0
 */
@RestController
@RequestMapping("/j6/finance/cashout/verify")
@Api(tags = "批量管理")
public class CashoutVerifyController implements CashoutApi {


    /**
     * 实现批量通过方法
     */
    @PostMapping("/batchPass")
    @ApiOperation("批量通过请款")
    @ApiOperationSupport(order = 1)
    @Override
    public JsonVO<Void> batchPass(BatchVerifyDTO dto) {
        return null;
    }

    /**
     * 实现批量驳回方法
     */
    @PostMapping("/batchReject")
    @ApiOperation("批量驳回请款")
    @ApiOperationSupport(order = 2)
    @Override
    public JsonVO<Void> batchReject(BatchVerifyDTO dto) {
        return null;
    }
}
