package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.dto.j4.student.StudentEnrollDTO;
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

    @PostMapping("/add-enroll")
    @ApiOperation(value = "新增学员报名", notes = "关联课程并初始化课时流水")
    public Result<Boolean> addStudentEnroll(@RequestBody StudentEnrollDTO enrollDTO) {
        // 基础校验
        if (enrollDTO.getStudentId() == null || enrollDTO.getCourseId() == null) {
            return Result.build(false, "报名失败：学员ID和课程ID不能为空");
        }

        boolean isSuccess = studentService.saveStudentEnroll(enrollDTO);
        return isSuccess ? Result.ok() : Result.build(false, "报名存入数据库失败");
    }

    /**
     * 获取学员详情
     */
    @GetMapping("/query-detail/id")
    @ApiOperation(value = "获取学员详细资料", notes = "根据ID查询单条详情")
    public Result<StudentDTO> queryStudentDetail(Integer id) {
        // Service 返回原始 DTO 对象
        StudentDTO detail = studentService.getStudentDetail(id);
        // 包装进 Result 的 result 字段
        return Result.build(detail);
    }

}