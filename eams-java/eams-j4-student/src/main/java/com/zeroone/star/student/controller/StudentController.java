package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.ResponseDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.CourseQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
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
    @GetMapping("/queryCourseStudent")
    @ApiOperation("获取开通指定课程学员列表（条件+分页）")
    public JsonVO<PageDTO<ResponseDTO>> queryCourseStudent(CourseQuery condition) {
        return null;
    }

    @Override
    @GetMapping("/listAllStudent")
    @ApiOperation("获取学员列表（条件+分页）")
    public JsonVO<PageDTO<ResponseDTO>> listAllStudent(StudentQuery condition) {
        return null;
    }
}
