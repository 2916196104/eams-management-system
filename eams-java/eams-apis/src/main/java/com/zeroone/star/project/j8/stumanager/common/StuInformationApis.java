package com.zeroone.star.project.j8.stumanager.common;

import com.zeroone.star.project.dto.j8.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.dto.j8.SaveStu.StuSignCourseDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

@Api(tags = "学员管理")
/**
 * 学员信息
 */
public interface StuInformationApis {

    @ApiOperation("保存学员")
    JsonVO<SaveStuDTO> saveStudent(SaveStuDTO stuSaveDTO);

    @ApiOperation("学员阶段设置")

    JsonVO<SaveStuAddDTO> setStudentStage(SaveStuAddDTO saveStuAddDTO);

    @ApiOperation("学员报名课程")

    JsonVO<StuSignCourseDTO> enrollCourse(StuSignCourseDTO stuSignCourseDTO);

    /**
     * 分页 + 条件 查询学员列表
     */
    JsonVO<PageDTO<StudentListVO>> queryStudents(StudentListQuery query);
    /**
     * 【开通指定课程的学员列表（含课次）】分页查询
     */
    JsonVO<PageDTO<StudentCourseVO>> queryStudentsByCourse(StudentCourseQuery condition);
}
