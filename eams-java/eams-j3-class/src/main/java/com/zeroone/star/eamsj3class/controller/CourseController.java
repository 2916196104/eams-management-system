package com.zeroone.star.eamsj3class.controller;

import com.zeroone.star.eamsj3class.service.ISubjectService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.AddCourseDTO;
import com.zeroone.star.project.dto.j3.course.SubjectDTO;
import com.zeroone.star.project.j3.course.CourseApis;
import com.zeroone.star.project.query.j3.course.CourseListQuery;
import com.zeroone.star.project.query.j3.course.SubjectQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.course.CourseDetailVO;
import com.zeroone.star.project.vo.j3.course.CourseListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
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

    @GetMapping("/query-courses-list")
    @ApiOperation("获取课程列表（条件 + 分页）")
    @Override
    public JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseListQuery courseListQuery) {
        return null;
    }

    @GetMapping("/query-one-course/{courseId}")
    @Override
    @ApiOperation("获取课程详情")
    public JsonVO<CourseDetailVO> queryCourseDetail(@PathVariable Long courseId) {
       return null;
    }

    @PostMapping("/add-course")
    @ApiOperation("保存课程")
    @Override
    public JsonVO<String> addCourse(@RequestBody AddCourseDTO addCourseDTO) {
        return null;
    }

    @DeleteMapping("/delete-courses")
    @Override
    @ApiOperation("删除课程（支持批量删除）")
    public JsonVO<String> deleteCourses(@RequestBody List<String> courseIds) {
        return null;
    }
    @GetMapping("query-subject-list")
    @Override
    @ApiOperation("获取科目列表（条件 + 分页）")
    public JsonVO<PageDTO<SubjectDTO>> querySubjectList(@Validated SubjectQuery courseListQuery) {
        return JsonVO.success(subjectService.querySubjectList(courseListQuery));
    }

    @GetMapping("query-subject-names")
    @ApiOperation(value = "查询科目名称列表")
    @Override
    public JsonVO<List<String>> querySubjectNames() {
        return JsonVO.success(subjectService.querySubjectNames());
    }

    @PutMapping("save-subject")
    @ApiOperation(value = "保存科目")
    @Override
    public JsonVO<String> saveSubject(@Validated @RequestBody SubjectDTO subjectDto) {
        return subjectService.saveSubject(subjectDto) ? JsonVO.success("保存成功") : JsonVO.fail("保存失败");
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
        return subjectService.deleteSubjects(subjectIds) ? JsonVO.success("删除成功") : JsonVO.fail("删除失败");
    }


}
