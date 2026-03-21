package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuSignCourseDTO;
import com.zeroone.star.project.j8.stumanager.common.StuInformationApis;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.stumanager.service.IStudentCourseService;
import com.zeroone.star.stumanager.service.IStudentService;
import com.zeroone.star.stumanager.service.impl.MsStuCouMapper;
import com.zeroone.star.stumanager.service.impl.MsStuMapper;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;

/**
 * 学员信息
 */
@Api(tags = "共用接口-学员信息")
@RequestMapping("/stu/common/stuInformation")
@RestController
public class StuInformationController implements StuInformationApis {

    @Resource
    IStudentService iStudentService;

    @Resource
    IStudentCourseService iStudentCourseService;

    @Resource
    MsStuMapper msStuMapper;

    @Resource
    MsStuCouMapper msStuCouMapper;

    //保存学员控制器
    @PostMapping("/save-student")
    @ApiOperation(value = "保存学员")
    @Override
    public JsonVO<SaveStuDTO> saveStudent(@Validated @RequestBody SaveStuDTO stuSaveDTO) {
        JsonVO<SaveStuDTO> jsonVO = new JsonVO<>();
        jsonVO.setData(stuSaveDTO);
        return jsonVO;
    }

    //切换学生状态
    @PostMapping("/set-studentStage")
    @ApiOperation(value = "切换学生状态")
    @Override
    public JsonVO<SaveStuAddDTO> setStudentStage(@Validated @RequestBody SaveStuAddDTO saveStuAddDTO) {
        JsonVO<SaveStuAddDTO> jsonVO = new JsonVO<>();
        jsonVO.setData(saveStuAddDTO);
        return jsonVO;
    }

    //报名课程
    @PostMapping("/enroll-Course")
    @ApiOperation(value = "报名课程")
    @Override
    public JsonVO<StuSignCourseDTO> enrollCourse(@Validated @RequestBody StuSignCourseDTO stuSignCourseDTO) {
        JsonVO<StuSignCourseDTO> jsonVO = new JsonVO<>();
        jsonVO.setData(stuSignCourseDTO);
        return jsonVO;
    }

    @GetMapping("/query-studentlist")
    @ApiOperation(value = "获取学员列表")
    @Override
    public JsonVO<PageDTO<StudentListVO>> queryStudents(StudentListQuery query) {
        return null;
    }
    @GetMapping("/query-listByCourse")
    @ApiOperation(value = "获取学员课程数据列表")
    @Override
    public JsonVO<PageDTO<StudentCourseVO>> queryStudentsByCourse(StudentCourseQuery condition) {
        return null;
    }
}
