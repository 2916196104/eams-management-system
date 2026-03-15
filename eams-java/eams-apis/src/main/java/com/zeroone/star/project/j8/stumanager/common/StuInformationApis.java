package com.zeroone.star.project.j8.stumanager.common;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.SaveStu.StuSignCourseDTO;
import com.zeroone.star.project.vo.JsonVO;
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
}
