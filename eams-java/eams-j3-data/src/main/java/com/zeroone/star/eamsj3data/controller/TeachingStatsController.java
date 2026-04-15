package com.zeroone.star.eamsj3data.controller;

import com.zeroone.star.eamsj3data.service.ClassHourStatsService;
import com.zeroone.star.eamsj3data.service.TeachEvaluationService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.data.TeachEvaluationDTO;
import com.zeroone.star.project.j3.data.TeachingStatsApis;
import com.zeroone.star.project.query.j3.data.ClassHourStatsQuery;
import com.zeroone.star.project.query.j3.data.TeachEvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.data.ClassHourStatsVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;


@RestController
@RequestMapping("j3-statis")
@Api(tags = "学评教，课时统计")
public class TeachingStatsController implements TeachingStatsApis {

    @Resource
    private TeachEvaluationService teachEvaluationService;

    @Resource
    private ClassHourStatsService classHourStatsService;

    @Override
    @GetMapping("/teachevaluation")
    @ApiOperation("学评教统计(排序）")
    public JsonVO<PageDTO<TeachEvaluationDTO>> queryTeachEvaluation(TeachEvaluationQuery query) {
        PageDTO<TeachEvaluationDTO> pageDTO = PageDTO.create(teachEvaluationService.queryTeachEvaluation(query));
        return JsonVO.success(pageDTO);
    }

    @Override
    @GetMapping("/class-hour-stats")
    @ApiOperation("课时统计")
    public JsonVO<PageDTO<ClassHourStatsVO>> queryClassHourStats(ClassHourStatsQuery query) {
        PageDTO<ClassHourStatsVO> pageDTO = PageDTO.create(classHourStatsService.queryClassHourStats(query));
        return JsonVO.success(pageDTO);
    }
}
