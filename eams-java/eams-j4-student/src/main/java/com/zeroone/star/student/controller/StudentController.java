package com.zeroone.star.student.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.CourseQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import org.springframework.web.bind.annotation.RestController;

/**
 * <p>
 * 学生表 前端控制器
 * </p>
 *
 * @author erji
 * @since 2026-03-15
 */
@RestController
@RequestMapping("/j4/student")
public class StudentController implements StudentApis {

    @GetMapping("/courseStudent")
    @Override
    @ApiOperation("获取开通指定课程学员列表（条件+分页）")
    public JsonVO<PageDTO<StudentDTO>> queryCourseStudent(CourseQuery condition) {
        return null;
    }

    @GetMapping("/listAll")
    @Override
    @ApiOperation("获取学员列表（条件+分页）")
    public JsonVO<PageDTO<StudentDTO>> listAllStudent(StudentQuery condition) {
        return null;
    }
}

