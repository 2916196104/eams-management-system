package com.zeroone.star.finance.controller;

import com.zeroone.star.finance.service.ClassConsumptionFeeService;
import com.zeroone.star.project.j6.finance.ClassConsumptionFeeApis;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.ClassConsumptionFeeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.ClassConsumptionFeeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


@RestController
@RequestMapping("/j6-finance/ccf")
@Api(tags = "销课课酬")
public class ClassConsumptionFeeController implements ClassConsumptionFeeApis {
    @Autowired
    private ClassConsumptionFeeService classConsumptionFeeService;


    @Override
    @ApiOperation(value = "分页查询销课课酬列表")
    @GetMapping("/queryPage")
    public JsonVO<PageDTO<ClassConsumptionFeeVO>> queryPage(ClassConsumptionFeeQuery condition) {

        return classConsumptionFeeService.listClassConsumptionFees(condition);
    }
}
