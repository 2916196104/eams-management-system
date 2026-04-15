package com.zeroone.star.eamsj3class.controller;

import com.zeroone.star.eamsj3class.service.CourseSectionService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseSectionDTO;
import com.zeroone.star.project.j3.course.CourseSectionApis;
import com.zeroone.star.project.query.CourseSectionPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;

@RestController
@RequestMapping("j3-course")
@Api(tags = "课程章节设置")
public class CourseSectionController implements CourseSectionApis {

    @Resource
    private CourseSectionService sectionService;
    @Override
    @GetMapping("/list")
    @ApiOperation("获取关联章节列表（条件+分页）")
    public JsonVO<PageDTO<CourseSectionDTO>> queryPage(@Valid CourseSectionPageQuery query) {
        PageDTO<CourseSectionDTO> pageResult = sectionService.queryPage(query);
        return JsonVO.success(pageResult);
    }

    @Override
    @PostMapping("/add")
    @ApiOperation("添加章节")
    public JsonVO<Long> addSection(@Valid @RequestBody CourseSectionDTO dto) {
        Long sectionId = sectionService.addSection(dto);
        return JsonVO.success(sectionId);
    }

    @Override
    @DeleteMapping("/delete/{id}")
    @ApiOperation("移除章节")
    @ApiImplicitParam(name = "id", value = "章节ID", required = true)
    public JsonVO<Void> deleteSection(@PathVariable Long id) {
        sectionService.deleteSection(id);
        return JsonVO.success(null);
    }
}