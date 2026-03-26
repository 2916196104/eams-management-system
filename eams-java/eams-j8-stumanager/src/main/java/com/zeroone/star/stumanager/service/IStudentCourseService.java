package com.zeroone.star.stumanager.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuChooseCourseDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuChooseStaffDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuSignCourseDTO;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.CourseQuery;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.stumanager.entity.StudentCourse;
import com.baomidou.mybatisplus.extension.service.IService;
import io.swagger.annotations.ApiOperation;

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
    JsonVO<StuSignCourseDTO> enrollCourse(StuSignCourseDTO stuSignCourseDTO);

    @ApiOperation("获取分页选择课程信息")
    JsonVO<PageDTO<StuChooseCourseDTO>> CourseSelect(CourseQuery query);

    @ApiOperation("获取分页经手人信息")
    JsonVO<PageDTO<StuChooseStaffDTO>> StaffSelect(StaffQuery query);

    /**
     * 按课程+学生姓名查询学员课程列表
     */
    PageDTO<StudentCourseVO> listStudentsByCourse(StudentCourseQuery condition);
}
