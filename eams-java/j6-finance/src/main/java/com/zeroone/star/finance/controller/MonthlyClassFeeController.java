package com.zeroone.star.finance.controller;

import com.zeroone.star.finance.service.MonthlyClassFeeService;
import com.zeroone.star.project.j6.finance.MonthlyClassFeeApis;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.MonthlyClassFeeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.MonthlyClassFeeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


@RestController
@RequestMapping("/j6-finance/mcf")
@Api(tags = "月课时费")
public class MonthlyClassFeeController implements MonthlyClassFeeApis {

    @Autowired
    private MonthlyClassFeeService monthlyClassFeeService;

    @Override
    @ApiOperation(value = "分页查询月课时费列表")
    @GetMapping("/queryPage")
    public JsonVO<PageDTO<MonthlyClassFeeVO>> queryPage(MonthlyClassFeeQuery condition) {
        return monthlyClassFeeService.listMonthlyClassFees(condition);
    }

}
