package com.zeroone.star.project.j3.course;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseSectionDTO;
import com.zeroone.star.project.query.CourseSectionPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

import javax.validation.Valid;

@Api(tags = "课程章节设置")
public interface CourseSectionApis {

    @ApiOperation("获取关联课程列表")
    JsonVO<PageDTO<CourseSectionDTO>> queryPage(@Valid CourseSectionPageQuery query);

    @ApiOperation("添加章节")
    JsonVO<Long> addSection(@Valid CourseSectionDTO dto);

    @ApiOperation("移除章节")
    JsonVO<Void> deleteSection(Long id);
}