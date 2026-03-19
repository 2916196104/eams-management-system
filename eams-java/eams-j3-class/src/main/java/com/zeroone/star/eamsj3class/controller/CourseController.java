package com.zeroone.star.eamsj3class.controller;

import com.zeroone.star.eamsj3class.service.ISubjectService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.SubjectDTO;
import com.zeroone.star.project.j3.course.CourseApis;
import com.zeroone.star.project.query.j3.course.SubjectQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 描述：课程controller
 * </p>
 * @author fish
 * @version 1.0.0
 */
@RestController
@RequestMapping("/course")
@Api(tags = "课程管理")
@Validated
public class CourseController implements CourseApis {

    @Resource
    private ISubjectService subjectService;

    @GetMapping("query-subject-list")
    @Override
    @ApiOperation("获取科目列表（条件 + 分页）")
    public JsonVO<PageDTO<SubjectDTO>> queryCourseList(@Validated SubjectQuery courseListQuery) {
        return null;
    }

    @GetMapping("query-subject-names")
    @ApiOperation(value = "查询科目名称列表")
    @Override
    public JsonVO<List<String>> querySubjectNames() {
        return null;
    }

    @PutMapping("save-subject")
    @ApiOperation(value = "保存科目")
    @Override
    public JsonVO<String> saveSubject(@Validated @RequestBody SubjectDTO subjectDto) {
        return null;
    }


    @DeleteMapping("delete-subject")
    @ApiOperation(value = "删除科目(支持批量删除)")
    @ApiImplicitParam(
            name = "subjectIds",
            value = "编号列表",
            required = true,
            dataType = "List",
            paramType = "body",
            example = "[\"1\",\"2\"]"
    )
    @Override
    public JsonVO<String> deleteSubjects(
            @ApiParam(value = "编号列表", required = true)
            @RequestBody
            List<String> subjectIds) {
        return null;
    }


}
