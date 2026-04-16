package com.zeroone.star.operation.controller;

import com.zeroone.star.operation.service.ICreditExchangeService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.CreditExchangeBatchAuditDTO;
import com.zeroone.star.project.j9.operation.CreditExchangeApis;
import com.zeroone.star.project.query.j9.operation.CreditExchangeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeBatchAuditVO;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;


/**
 * 积分兑换Controller
 */
@RestController
@RequestMapping("credit-exchange")
@Api(tags = "积分兑换")
public class CreditExchangeController implements CreditExchangeApis {

    @Resource
    private ICreditExchangeService creditExchangeService;

    @Override
    @ApiOperation(value = "查询兑换申请列表（条件+分页）")
    @GetMapping("/list")
    public JsonVO<PageDTO<CreditExchangeVO>> queryAll(CreditExchangeQuery condition) {
        PageDTO<CreditExchangeVO> result = creditExchangeService.listCreditExchanges(condition);
        return JsonVO.success(result);
    }

    @Override
    @ApiOperation(value = "批量审核兑换申请", notes = "审核状态必填，审核说明可选")
    @PostMapping("/batch-audit")
    public JsonVO<CreditExchangeBatchAuditVO> modifyExchangeAudit(
            @Validated @RequestBody CreditExchangeBatchAuditDTO auditDTO) {
        CreditExchangeBatchAuditVO result = creditExchangeService.updateExchangeAudit(auditDTO);
        if (result.getAllSuccess()) {
            return JsonVO.success(result);
        }
        return JsonVO.fail(result);
    }
}

