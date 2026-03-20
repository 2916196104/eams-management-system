package com.zeroone.star.j5.evaluation.controller;

import com.zeroone.star.j5.edu.EvaluationApis;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.edu.EvaluationDTO;
import com.zeroone.star.project.query.j5.edu.EvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("j5/edu/evaluation")
@Api(tags="课后点评")
public class EvaluationController implements EvaluationApis {
    @Override
    @GetMapping
    @ApiOperation("获取获取课后点评列表（条件+分页）")
    public JsonVO<PageDTO<EvaluationDTO>> queryPage(@RequestBody EvaluationQuery condition) {
        return null;
    }

    @PostMapping
    @Override
    @ApiOperation("保存点评")
    public JsonVO<Long> saveEvaluation(@RequestBody EvaluationDTO evaluationDTO) {
        return null;
    }
}
