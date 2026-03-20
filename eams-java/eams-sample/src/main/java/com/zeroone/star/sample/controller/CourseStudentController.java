package com.zeroone.star.sample.controller;

import com.zeroone.star.j5.edu.CourseStudentApis;
import com.zeroone.star.project.dto.j5.edu.CourseStudentDTO;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("j5/edu/courseStudent")
@Api(tags="随课生")
public class CourseStudentController implements CourseStudentApis {
    @Override
    @ApiOperation("添加随课生")
    @PostMapping
    public JsonVO<Long> saveCourseStudent(@RequestBody CourseStudentDTO courseStudentDTO) {
        return null;
    }
}
