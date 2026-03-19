package com.zeroone.star.academic.controller;

import com.zeroone.star.academic.service.IAcademicFinanceService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.j4.academic.AcademicApis;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

/**
 * <p>
 * 描述：学员模块缴欠费与退费控制器
 * </p>
 */
@Validated
@RestController
@RequestMapping("/j4/academic")
@Api(tags = "学员模块财务接口")
public class AcademicController implements AcademicApis {
    @Resource
    private IAcademicFinanceService academicFinanceService;

    @ApiOperation(value = "分页查询缴欠费与退费记录")
    @GetMapping("/finance/page")
    @Override
    public JsonVO<PageDTO<FinanceDTO>> queryFinancePage(FinanceQuery query) {
        return JsonVO.success(academicFinanceService.queryFinancePage(query));
    }

    @ApiOperation(value = "办理缴欠费")
    @PostMapping("/finance/pay-debt")
    @Override
    public JsonVO<FinanceDTO> payDebt(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(academicFinanceService.payDebt(financeDTO));
    }

    @ApiOperation(value = "发起退费申请")
    @PostMapping("/refund/apply")
    @Override
    public JsonVO<FinanceDTO> applyRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(academicFinanceService.applyRefund(financeDTO));
    }

    @ApiOperation(value = "审核退费申请")
    @PostMapping("/refund/audit")
    @Override
    public JsonVO<FinanceDTO> auditRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(academicFinanceService.auditRefund(financeDTO));
    }

    @ApiOperation(value = "完成退费")
    @PostMapping("/refund/complete")
    @Override
    public JsonVO<FinanceDTO> completeRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(academicFinanceService.completeRefund(financeDTO));
    }
}
