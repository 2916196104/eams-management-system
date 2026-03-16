package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {

    //获取学生信息列表
    @ApiOperation("获取学生信息列表")
    @GetMapping("/queryPage")
    @Override
    public JsonVO<PageDTO<StudentDTO>> queryPage(StudentQuery condition) {
        return null;
    }

    //获取跟进记录列表，保存查询信息
    @Override

    public JsonVO<String> saveStudent(StudentDTO studentDTO) {
        return null;
    }

    //更新学生信息
    @Override
    public JsonVO<String> updateStudent(StudentDTO studentDTO) {
        return null;
    }

    //获取跟进记录列表，保存查询信息
    @Override
    public JsonVO<PageDTO<FollowUpDTO>> followUp(FollowUpQuery query) {
        return null;
    }
}
