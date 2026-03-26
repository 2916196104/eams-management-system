package com.zeroone.star.finance.controller;

import com.zeroone.star.finance.service.impl.CashoutServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.BatchVerifyDTO;
import com.zeroone.star.project.dto.j6.finance.CashoutAddDTO;
import com.zeroone.star.project.j6.finance.CashoutApis;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;
import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;

/**
 * 请款管理接口实现
 */
@RestController
@RequestMapping("/j6/finance/cashout")
@Api(tags = "请款管理")
public class CashoutController implements CashoutApis {

    /**
     * 请款列表查询（条件+分页）
     */
    @GetMapping("/list")
    @ApiOperation("请款列表查询（条件+分页）")
    @ApiOperationSupport(order = 1)
    @Override
    public JsonVO<PageDTO<CashoutListVO>> queryCashoutPage(CashoutListQuery query) {
        // TODO 调用 Service 完成查询，这里先返回 null
        return null;
    }

    /**
     * 请款信息详情查询
     */
    @GetMapping("/detail/{id}")
    @ApiOperation("请款信息详情查询")
    @ApiOperationSupport(order = 2)
    @Override
    public JsonVO<CashoutDetailVO> getCashoutDetail(@PathVariable("id") Long id) {
        // TODO 调用 Service 查询详情，这里先返回 null
        return null;
    }

    @PostMapping("/save")
    @ApiOperation(value = "保存请款申请")
    @Override
    public JsonVO<Long> saveCashout(@Validated @RequestBody CashoutAddDTO cashoutAddDTO) {
        return null;
    }

    @PutMapping("/cancel/{id}")
    @ApiOperation(value = "作废请款申请")
    @Override
    public JsonVO<Long> cancelCashout(@PathVariable Long id) {
        return null;
    }

    /**
     * 实现批量通过方法
     */
    @PostMapping("/batchPass")
    @ApiOperation("批量通过请款")
    @ApiOperationSupport(order = 1)
    @Override
    public JsonVO<Void> batchPass(@RequestBody BatchVerifyDTO dto) {
        return null;
    }

    /**
     * 实现批量驳回方法
     */
    @PostMapping("/batchReject")
    @ApiOperation("批量驳回请款")
    @ApiOperationSupport(order = 2)
    @Override
    public JsonVO<Void> batchReject(@RequestBody BatchVerifyDTO dto) {
        return null;
    }
}