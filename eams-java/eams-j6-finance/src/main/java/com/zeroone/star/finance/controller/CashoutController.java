package com.zeroone.star.finance.controller;

import com.zeroone.star.finance.service.ICashoutService;
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
@RequestMapping("/j6-finance/cashout")
@Api(tags = "请款管理")
public class CashoutController implements CashoutApis {

    @Resource
    ICashoutService cashoutService;
    /**
     * 请款列表查询（条件+分页）
     */
    @GetMapping("/list")
    @ApiOperation("请款列表查询（条件+分页）")
    @ApiOperationSupport(order = 1)
    @Override
    public JsonVO<PageDTO<CashoutListVO>> queryCashoutPage(CashoutListQuery query) {
        try {
            PageDTO<CashoutListVO> page = cashoutService.queryCashoutPage(query);
            return JsonVO.success(page);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 请款信息详情查询
     */
    @GetMapping("/detail/{id}")
    @ApiOperation("请款信息详情查询")
    @ApiOperationSupport(order = 2)
    @Override
    public JsonVO<CashoutDetailVO> getCashoutDetail(@PathVariable("id") Long id) {
        CashoutDetailVO detail = cashoutService.getCashoutDetail(id);
        if (detail == null) {
            return JsonVO.fail("请款记录不存在");
        }
        return JsonVO.success(detail);
    }

    /**
     * 保存请款申请
     */
    @PostMapping("/save")
    @ApiOperation(value = "保存请款申请")
    @ApiOperationSupport(order = 3)
    @Override
    public JsonVO<Long> saveCashout(@Validated @RequestBody CashoutAddDTO cashoutAddDTO) {
        try {
            Long id = cashoutService.saveCashout(cashoutAddDTO);
            return JsonVO.success(id);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 作废请款申请
     */
    @PutMapping("/cancel/{id}")
    @ApiOperation(value = "作废请款申请")
    @ApiOperationSupport(order = 4)
    @Override
    public JsonVO<Long> cancelCashout(@PathVariable Long id) {
        try {
            cashoutService.cancelCashout(id);
            return JsonVO.success(id);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 实现批量通过方法
     */
    @PostMapping("/batchPass")
    @ApiOperation("批量通过请款")
    @ApiOperationSupport(order = 1)
    @Override
    public JsonVO<Void> batchPass(@RequestBody BatchVerifyDTO dto) {
        try {
            // 校验ID列表不能为空
            if (dto.getIds() == null || dto.getIds().isEmpty()) {
                return JsonVO.fail("请选择至少一条请款记录");
            }
            // 设置审核状态为通过（1）
            dto.setVerifyState(1);
            cashoutService.batchVerify(dto);
            return JsonVO.success(null);
        } catch (Exception e) {
            return JsonVO.fail("批量通过请款失败：" + e.getMessage());
        }
    }

    /**
     * 实现批量驳回方法
     */
    @PostMapping("/batchReject")
    @ApiOperation("批量驳回请款")
    @ApiOperationSupport(order = 2)
    @Override
    public JsonVO<Void> batchReject(@RequestBody BatchVerifyDTO dto) {
        try {
            // 校验ID列表不能为空
            if (dto.getIds() == null || dto.getIds().isEmpty()) {
                return JsonVO.fail("请选择至少一条请款记录");
            }
            // 校验驳回备注必填
            if (dto.getVerifyRemark() == null || dto.getVerifyRemark().trim().isEmpty()) {
                return JsonVO.fail("驳回请款时必须填写备注");
            }
            // 设置审核状态为驳回（2）
            dto.setVerifyState(2);
            cashoutService.batchVerify(dto);
            return JsonVO.success(null);
        } catch (Exception e) {
            return JsonVO.fail("批量驳回请款失败：" + e.getMessage());
        }
    }
}