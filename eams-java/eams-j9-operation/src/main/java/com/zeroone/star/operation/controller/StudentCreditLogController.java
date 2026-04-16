package com.zeroone.star.operation.controller;

import com.zeroone.star.operation.service.IStudentCreditLogService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.StudentCreditAdjustDTO;
import com.zeroone.star.project.j9.operation.StudentCreditLogApis;
import com.zeroone.star.project.query.j9.operation.StudentCreditLogQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.StudentCreditAdjustVO;
import com.zeroone.star.project.vo.j9.operation.StudentCreditLogVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;

/**
 * 学生积分记录 Controller
 */
@RestController
@RequestMapping("credit-log")
@Api(tags = "学生积分记录管理")
public class StudentCreditLogController implements StudentCreditLogApis {

    @Resource
    private IStudentCreditLogService studentCreditLogService;

    @Override
    @ApiOperation(value = "查询学生积分记录列表（条件+分页）")
    @GetMapping("/list")
    public JsonVO<PageDTO<StudentCreditLogVO>> queryCreditLogList(StudentCreditLogQuery condition) {
        PageDTO<StudentCreditLogVO> result = studentCreditLogService.listCreditLogs(condition);
        return JsonVO.success(result);
    }

    @Override
    @ApiOperation(value = "调整学生积分", notes = "选择学生和调整积分数必填，调整原因选填")
    @PostMapping("/adjust")
    public JsonVO<StudentCreditAdjustVO> modifyCredit(
            @Validated @RequestBody StudentCreditAdjustDTO adjustDTO) {
        StudentCreditAdjustVO result = studentCreditLogService.updateStudentCredit(adjustDTO);
        if (result.getSuccess()) {
            return JsonVO.success(result);
        }
        return JsonVO.fail(result);
    }
}
