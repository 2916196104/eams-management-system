package com.zeroone.star.project.j8.stumanager.common;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.SaveStu.ChangeStuStageDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.StuSignCourse.*;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.CourseQuery;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.SaveStu.DictVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

import javax.validation.Valid;
import java.util.List;

@Api(tags = "学员管理")
/**
 * 学员信息
 */
public interface StuInformationApis {

    @ApiOperation("保存学员信息")
    JsonVO<SaveStuDTO> saveStudent(SaveStuDTO saveStuDTO);

    @ApiOperation("修改学员状态")
    JsonVO<ChangeStuStageDTO> updateStudentStage(ChangeStuStageDTO changeStuStageDTO);

    @ApiOperation("学员报名课程")
    JsonVO<StuSignCourseDTO> enrollCourse(@Valid StuSignCourseDTO stuSignCourseDTO);

    @ApiOperation("获取分页选择课程信息")
    JsonVO<PageDTO<StuChooseCourseDTO>> CourseSelect(CourseQuery query);

    @ApiOperation("获取分页经手人信息")
    JsonVO<PageDTO<StuChooseStaffDTO>> StaffSelect(StaffQuery query);

    @ApiOperation("获取亲属关系字典")
    JsonVO<List<DictVO>> listFamilyRel();

    @ApiOperation("获取年级下拉字典")
    JsonVO<List<DictVO>> listGradeDict();

    @ApiOperation("获取来源下拉字典")
    JsonVO<List<DictVO>> listJoinWayDict();


}
