package com.zeroone.star.project.j8.stumanager.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.stumanager.StudentHeadImgDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuSignCourseDTO;
import com.zeroone.star.project.query.j8.stumanager.StudentQuery;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentVO;
import io.swagger.annotations.ApiOperation;

/**
 * 学员信息
 */
public interface StuInformationApis {

    JsonVO<SaveStuDTO> saveStudent(SaveStuDTO stuSaveDTO);

    JsonVO<SaveStuAddDTO> setStudentStage(SaveStuAddDTO saveStuAddDTO);

    @ApiOperation("学员报名课程")
    JsonVO<StuSignCourseDTO> enrollCourse(StuSignCourseDTO stuSignCourseDTO);

    @ApiOperation("查询学员详细信息")
    JsonVO<StudentVO> getStudentDetail(StudentQuery query);

    @ApiOperation("修改学员头像")
    JsonVO<String> updateStudentHeadImg(StudentHeadImgDTO studentHeadImgDTO);

    /**
     * 分页 + 条件 查询学员列表
     */
    @ApiOperation("分页条件查询学员列表")
    JsonVO<PageDTO<StudentListVO>> queryStudents(StudentListQuery query);

    /**
     * 【开通指定课程的学员列表（含课次）】分页查询
     */
    @ApiOperation("开通指定课程的学员列表分页查询")
    JsonVO<PageDTO<StudentCourseVO>> queryStudentsByCourse(StudentCourseQuery condition);
}