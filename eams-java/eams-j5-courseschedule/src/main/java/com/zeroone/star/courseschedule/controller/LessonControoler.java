package com.zeroone.star.courseschedule.controller;

import com.zeroone.star.courseschedule.dto.j5.org.DTO.LessonDTO;
import com.zeroone.star.courseschedule.dto.j5.org.DTO.LessonListDTO;
import com.zeroone.star.courseschedule.query.j5.org.LessonQuery;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.org.LessonApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController("j5/lesson")
@Api(tags="课程表")
public class LessonControoler implements LessonApis {

    @GetMapping
    @ApiOperation("获取课表日历（条件）")
    @Override
    public JsonVO<List<LessonDTO>> queryList(LessonQuery condition) {
        return null;
    }

    @GetMapping
    @ApiOperation("获取课次列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<LessonListDTO>> queryPage(LessonQuery condition) {
        return null;
    }

    @GetMapping
    @ApiOperation("获取课次详情")
    @Override
    public JsonVO<List<LessonListDTO>> queryNameList(String name) {
        return null;
    }
}
