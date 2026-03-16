package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.CourseCounterVO;
import com.zeroone.star.project.vo.j4.student.StudentScheduleVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {

    @Override
    @PostMapping("/getCourseCounter")
    @ApiOperation(value = "获取课程统计")
    public JsonVO<PageDTO<CourseCounterVO>> getCourseCounter(StudentQuery studentQuery) {
        return null;
    }

    @Override
    @PostMapping("/getStudentSchedule")
    @ApiOperation(value = "获取课表")
    public JsonVO<StudentScheduleVO> getStudentSchedule(StudentQuery studentQuery) {
        return null;
    }
}