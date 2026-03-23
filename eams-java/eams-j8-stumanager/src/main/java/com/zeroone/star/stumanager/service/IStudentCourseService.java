package com.zeroone.star.stumanager.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.StuSignCourse.*;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.CourseQuery;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.stumanager.entity.StudentCourse;
import com.baomidou.mybatisplus.extension.service.IService;
import io.swagger.annotations.ApiOperation;

import javax.validation.Valid;
import java.util.List;

/**
 * <p>
 * 报名签约表 服务类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
public interface IStudentCourseService extends IService<StudentCourse> {


    @ApiOperation("学员报名课程")
    JsonVO<StuSignCourseDTO> enrollCourse(@Valid StuSignCourseAddDTO stuSignCourseAddDTO);

    @ApiOperation("获取课程选择列表")
    JsonVO<PageDTO<StuChooseCourseDTO>> listCourseSelect(CourseQuery query);

    @ApiOperation("获取经手人选择列表")
    JsonVO<PageDTO<StuChooseStaffDTO>> listStaffSelect(StaffQuery query);

}
