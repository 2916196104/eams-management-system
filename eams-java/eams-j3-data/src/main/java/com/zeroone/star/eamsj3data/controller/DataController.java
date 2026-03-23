package com.zeroone.star.eamsj3data.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.data.ClassHourStatsDTO;
import com.zeroone.star.project.dto.j3.data.TeachEvaluationDTO;
import com.zeroone.star.project.j3.data.DataApis;
import com.zeroone.star.project.query.j3.data.ClassHourStatsQuery;
import com.zeroone.star.project.query.j3.data.TeachEvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


@RestController
@RequestMapping("j3/statis")
@Api(tags = "学评教，课时统计")
public class DataController implements DataApis {
    @Override
    @GetMapping("/lessonStatis")
    @ApiOperation("学评教统计")
    public JsonVO<PageDTO<TeachEvaluationDTO>> queryTeachEvaluation(TeachEvaluationQuery query) {
        return null;
    }

    @Override
    @GetMapping("/sort")
    @ApiOperation("学评教统计排序")
    public JsonVO<PageDTO<TeachEvaluationDTO>> queryTeachEvaluationBySort(TeachEvaluationQuery query) {
        return null;
    }

    @Override
    @GetMapping("/class-hour-stats")
    @ApiOperation("课时统计")
    public JsonVO<PageDTO<ClassHourStatsDTO>> queryClassHourStats(ClassHourStatsQuery query) {
        return null;
    }
}
