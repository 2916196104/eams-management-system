package com.zeroone.star.project.j8.stumanager.common;

import com.zeroone.star.project.dto.j8.stumanager.common.StudentDTO;
import com.zeroone.star.project.query.j8.stumanager.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentAvatarVo;
import com.zeroone.star.project.vo.j8.stumanager.StudentVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

@Api(tags = "学员管理")
/**
 * 学员信息
 */
public interface StuInformationApis {

    @ApiOperation("保存学员")
    JsonVO<Void> saveStudent();

    @ApiOperation("学员阶段设置")
    JsonVO<Void> setStudentStage();

    @ApiOperation("学员报名课程")
    JsonVO<Void> enrollCourse();

    @ApiOperation("查询学员详细信息")
    JsonVO<StudentVO> getStudentDetail(StudentQuery query);


    @ApiOperation("修改学员头像")
    JsonVO<StudentAvatarVo> updateStudentAvatar(String avatarUrl);
}
