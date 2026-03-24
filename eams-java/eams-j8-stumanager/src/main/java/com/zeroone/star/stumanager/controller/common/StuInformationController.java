package com.zeroone.star.stumanager.controller.common;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuSignCourseDTO;
import com.zeroone.star.project.dto.j8.stumanager.StudentAvatarDTO;
import com.zeroone.star.project.j8.stumanager.common.StuInformationApis;
import com.zeroone.star.project.query.j8.stumanager.StudentQuery;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentAvatarVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentVO;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.service.IStudentCourseService;
import com.zeroone.star.stumanager.service.IStudentService;
import com.zeroone.star.stumanager.service.impl.MsStuCouMapper;
import com.zeroone.star.stumanager.service.impl.MsStuMapper;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.BeanUtils;
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
        return JsonVO.success(stuSaveDTO);
    }

    //切换学生状态
    @PostMapping("/set-studentStage")
    @ApiOperation(value = "切换学生状态")
    @Override
    public JsonVO<SaveStuAddDTO> setStudentStage(@Validated @RequestBody SaveStuAddDTO saveStuAddDTO) {
        JsonVO<SaveStuAddDTO> jsonVO = new JsonVO<>();
        jsonVO.setData(saveStuAddDTO);
        return JsonVO.success(saveStuAddDTO);
    }

    //报名课程
    @PostMapping("/enroll-Course")
    @ApiOperation(value = "报名课程")
    @Override
    public JsonVO<StuSignCourseDTO> enrollCourse(@Validated @RequestBody StuSignCourseDTO stuSignCourseDTO) {
        JsonVO<StuSignCourseDTO> jsonVO = new JsonVO<>();
        jsonVO.setData(stuSignCourseDTO);
        return JsonVO.success(stuSignCourseDTO);
    }

    @Override
    @GetMapping("/get-studentDetail")
    @ApiOperation(value = "查询学员详细信息")
    public JsonVO<StudentVO> getStudentDetail(StudentQuery query) {
        if (query == null || query.getId() == null) {
            return JsonVO.fail("学员ID不能为空");
        }
        LambdaQueryWrapper<Student> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(Student::getId, query.getId());
        queryWrapper.like(StringUtils.isNotEmpty(query.getName()), Student::getName, query.getName());
        queryWrapper.eq(StringUtils.isNotEmpty(query.getBranchSchool()), Student::getSchoolId, query.getBranchSchool());
        queryWrapper.eq(StringUtils.isNotEmpty(query.getGrade()), Student::getGrade, query.getGrade());
        queryWrapper.like(StringUtils.isNotEmpty(query.getTeacherName()), Student::getCounselor, query.getTeacherName());//StudentVo:counselor,StudentQuery:teacherName;
        Student student=iStudentService.getOne(queryWrapper);
        if(student == null){
            return JsonVO.fail("未找到该学员信息");
        }
        StudentVO studentVO=new StudentVO();
        BeanUtils.copyProperties(student,studentVO);
        return JsonVO.success(studentVO);
    }

    @Override
    @PutMapping("/update-studentAvatar")
    @ApiOperation(value = "修改学员头像")
    public JsonVO<StudentAvatarVO> updateStudentAvatar(@Validated @RequestBody StudentAvatarDTO studentAvatarDTO ) {
        LambdaUpdateWrapper<Student> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.eq(Student::getId,studentAvatarDTO.getStudentId());
        updateWrapper.set(Student::getHeadImg,studentAvatarDTO.getAvatarUrl());//Student:headImg
        boolean success = iStudentService.update(updateWrapper);
        if(!success){
            return JsonVO.fail("修改头像失败");
        }
        StudentAvatarVO studentAvatarVO=new StudentAvatarVO();
        studentAvatarVO.setStudentId(studentAvatarDTO.getStudentId());
        studentAvatarVO.setAvatarUrl(studentAvatarDTO.getAvatarUrl());
        return JsonVO.success(studentAvatarVO);
    }

    @GetMapping("/query-studentlist")
    @ApiOperation(value = "获取学员列表")
    @Override
    public JsonVO<PageDTO<StudentListVO>> queryStudents(StudentListQuery query) {
        PageDTO<StudentListVO> pageDTO = new PageDTO<>();
        return JsonVO.success(pageDTO);
    }
    @GetMapping("/query-listByCourse")
    @ApiOperation(value = "获取学员课程数据列表")
    @Override
    public JsonVO<PageDTO<StudentCourseVO>> queryStudentsByCourse(StudentCourseQuery condition) {
        return JsonVO.success(null);
    }
}
