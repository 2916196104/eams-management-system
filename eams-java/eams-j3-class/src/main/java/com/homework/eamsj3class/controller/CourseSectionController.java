package com.homework.eamsj3class.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseSectionDTO;
import com.zeroone.star.project.j3.course.CourseSectionApis;
import com.zeroone.star.project.query.CourseSectionPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

@RestController
@RequestMapping("j3/cs")
@Api(tags = "课程章节设置")
public class CourseSectionController implements CourseSectionApis {

    @Override
    @GetMapping
    @ApiOperation("获取关联章节列表（条件+分页）")
    public JsonVO<PageDTO<CourseSectionDTO>> queryPage(@Valid CourseSectionPageQuery query) {
        return null;
    }

    @Override
    @PostMapping
    @ApiOperation("添加章节")
    public JsonVO<Long> addSection(@Valid @RequestBody CourseSectionDTO dto) {
        return null;
    }

    @Override
    @DeleteMapping
    @ApiOperation("移除章节")
    @ApiImplicitParam(name = "id", value = "章节ID", required = true)
    public JsonVO<Void> deleteSection(@PathVariable Long id) {
        return null;
    }
}