package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.student.service.IStudentFinanceService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {
    @Resource
    private IStudentFinanceService studentFinanceService;

    @ApiOperation(value = "分页查询缴欠费与线下退费记录")
    @GetMapping("/finance/page")
    @Override
    public JsonVO<PageDTO<FinanceDTO>> queryFinancePage(FinanceQuery query) {
        return JsonVO.success(studentFinanceService.queryFinancePage(query));
    }

    @ApiOperation(value = "办理缴欠费")
    @PostMapping("/finance/pay-debt")
    @Override
    public JsonVO<FinanceDTO> payDebt(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(studentFinanceService.payDebt(financeDTO));
    }

    @ApiOperation(value = "发起退费申请")
    @PostMapping("/refund/apply")
    @Override
    public JsonVO<FinanceDTO> applyRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(studentFinanceService.applyRefund(financeDTO));
    }

    @ApiOperation(value = "审核退费申请")
    @PostMapping("/refund/audit")
    @Override
    public JsonVO<FinanceDTO> auditRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(studentFinanceService.auditRefund(financeDTO));
    }

    @ApiOperation(value = "完成退费")
    @PostMapping("/refund/complete")
    @Override
    public JsonVO<FinanceDTO> completeRefund(@RequestBody FinanceDTO financeDTO) {
        return JsonVO.success(studentFinanceService.completeRefund(financeDTO));
    }
}
