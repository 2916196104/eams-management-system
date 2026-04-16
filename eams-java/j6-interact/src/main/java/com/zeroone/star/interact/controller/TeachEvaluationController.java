package com.zeroone.star.interact.controller;

import com.zeroone.star.interact.service.ITeachEvaluationService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.TeachEvaluationDTO;
import com.zeroone.star.project.j6.interact.TeachEvaluationApis;
import com.zeroone.star.project.query.j6.interact.TeachEvaluationQuery;
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
@RequestMapping("/j6-interact/teachEvaluation")
@Api(tags = "学评教")
public class TeachEvaluationController implements TeachEvaluationApis {

    @Resource
    private ITeachEvaluationService teachEvaluationService;

    @Override
    @GetMapping
    @ApiOperation("获取学生点评列表（条件+分页）")
    public JsonVO<PageDTO<TeachEvaluationDTO>> queryPage(@Validated TeachEvaluationQuery condition) {
        PageDTO<TeachEvaluationDTO> result = teachEvaluationService.queryPage(condition);
        return JsonVO.success(result);
    }
}
