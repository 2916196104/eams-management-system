package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.LessonSummaryVO;
import com.zeroone.star.project.vo.j4.student.StudentDetailVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;


import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.vo.j4.student.StudentDetailVO;
import com.zeroone.star.project.vo.j4.student.LessonSummaryVO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.PageDTO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

@Api(tags = "Student Course Interface")
public interface StudentApis {
    @ApiOperation("保存学员")
    @PostMapping("/student/save-student")
    JsonVO<String> saveStudent(@RequestBody StudentDTO dto);

    @ApiOperation("获取学员课次数据")
    @GetMapping("/student/query-course-times")
    JsonVO<StudentDetailVO> queryCourseTimes(@RequestParam String studentId);

    @ApiOperation("获取课时汇总列表")
    @PostMapping("/student/list-hour-summary")
    JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(@RequestBody StudentQuery query);
}