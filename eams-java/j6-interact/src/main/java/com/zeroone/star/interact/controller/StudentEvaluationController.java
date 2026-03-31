package com.zeroone.star.interact.controller;

import com.zeroone.star.interact.service.IStudentEvaluationService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.StudentEvaluationDTO;
import com.zeroone.star.project.j6.interact.StudentEvaluationApis;
import com.zeroone.star.project.query.j6.interact.StudentEvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@Validated
@RestController
@RequestMapping("/j6-interact/studentEvaluation")
@Api(tags = "教评学")
public class StudentEvaluationController implements StudentEvaluationApis {

    @Resource
    private IStudentEvaluationService studentEvaluationService;

    @Override
    @GetMapping
    @ApiOperation("获取教师点评列表（条件+分页）")
    public JsonVO<PageDTO<StudentEvaluationDTO>> queryPage(@Validated StudentEvaluationQuery condition) {
        PageDTO<StudentEvaluationDTO> result = studentEvaluationService.queryPage(condition);
        return JsonVO.success(result);
    }
}
