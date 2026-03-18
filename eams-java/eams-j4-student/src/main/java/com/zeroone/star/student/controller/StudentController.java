package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.student.service.StudentService;
import io.seata.core.model.Result;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
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

    @Autowired
    private StudentService studentService;

    /**
     * 学员阶段设置
     */
    @PutMapping("/modify-stage")
    @ApiOperation(value = "设置学员阶段状态", notes = "修改学员当前学习阶段")
    public Result<Boolean> modifyStudentStage(@RequestBody StudentDTO studentDTO) {
        // Service 返回原始 boolean
        boolean success = studentService.updateStudentStage(studentDTO);
        // 在 Controller 层进行 Result 包装
        return success ? Result.ok() : Result.build(false, "阶段更新失败");
    }

    /**
     * 学员报名课程
     */
    @PostMapping("/add-course")
    @ApiOperation(value = "学员报名课程", notes = "关联学员与课程记录")
    public Result<Boolean> addStudentCourse(@RequestBody StudentDTO studentDTO) {
        boolean success = studentService.saveStudentCourse(studentDTO);
        return success ? Result.ok() : Result.build(false, "报名存入失败");
    }

    /**
     * 获取学员详情
     */
    @GetMapping("/query-detail")
    @ApiOperation(value = "获取学员详细资料", notes = "根据ID查询单条详情")
    public Result<StudentDTO> queryStudentDetail(StudentQuery studentQuery) {
        // Service 返回原始 DTO 对象
        StudentDTO detail = studentService.getStudentDetail(studentQuery);
        // 包装进 Result 的 result 字段
        return Result.build(detail);
    }

}