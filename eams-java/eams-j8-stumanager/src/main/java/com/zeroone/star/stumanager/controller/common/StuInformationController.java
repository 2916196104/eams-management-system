package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.j8.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.SaveStu.StuSignCourseDTO;
import com.zeroone.star.project.j8.stumanager.common.StuInformationApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.SaveStu.StuSaveVO;
import com.zeroone.star.stumanager.service.IStudentCourseService;
import com.zeroone.star.stumanager.service.IStudentService;
import com.zeroone.star.stumanager.service.impl.MsStuCouMapper;
import com.zeroone.star.stumanager.service.impl.MsStuMapper;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
@RequestMapping("/StuInformation")
@Api(tags = "公用接口")
@Validated
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
}
