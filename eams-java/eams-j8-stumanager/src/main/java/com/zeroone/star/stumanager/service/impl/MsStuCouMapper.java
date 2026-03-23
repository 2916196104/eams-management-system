package com.zeroone.star.stumanager.service.impl;

import com.zeroone.star.project.dto.j8.StuSignCourse.*;
import com.zeroone.star.stumanager.entity.Staff;
import com.zeroone.star.stumanager.entity.StudentCourse;
import org.mapstruct.Mapper;

/**
 * <p>
 * 描述：StudentCourse对应MapStruct映射接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
//注入到spring容器
@Mapper(componentModel = "spring")
public interface MsStuCouMapper {
    /**
     * DO映射DTO（StudentCourse）
     * @param entity 实体
     * @return StuSignCourseDTO
     */
    StuSignCourseDTO studentCourseToStuSignCourseDto(StudentCourse entity);

    /**
     * addDTO映射实体（StudentCourse）
     * @param dto StuSignCourseAddDTO
     * @return 实体
     */
    StudentCourse addDtoToStudentCourse(StuSignCourseAddDTO dto);

    /**
     * DTO映射实体（StudentCourse）
     * @param dto StuSignCourseDTO
     * @return 实体
     */
    StudentCourse stuSignCourseDtoToStudentCourse(StuSignCourseDTO dto);

    /**
     * DO映射DTO（Staff）
     * @param entity 实体
     * @return StuChooseStaffDTO
     */
    StuChooseStaffDTO staffToStuChooseStaffDto(Staff entity);

    /**
     * addDTO映射实体（Staff）
     * @param dto StuChooseStaffAddDTO
     * @return 实体
     */
    Staff addDtoToStaff(StuChooseStaffAddDTO dto);

    /**
     * DTO映射实体（Staff）
     * @param dto StuChooseStaffDTO
     * @return 实体
     */
    Staff stuChooseStaffDtoToStaff(StuChooseStaffDTO dto);

    // ============ 新增 StuChooseCourseDTO/AddDTO 映射方法 ============
    /**
     * 实体映射DTO（StudentCourse -> StuChooseCourseDTO）
     * @param entity 学生课程实体
     * @return 课程选择DTO
     */
    StuChooseCourseDTO studentCourseToStuChooseCourseDto(StudentCourse entity);

    /**
     * AddDTO映射实体（StuChooseCourseAddDTO -> StudentCourse）
     * @param dto 课程选择新增DTO
     * @return 学生课程实体
     */
    StudentCourse stuChooseCourseAddDtoToStudentCourse(StuChooseCourseAddDTO dto);

    /**
     * DTO映射实体（StuChooseCourseDTO -> StudentCourse）
     * @param dto 课程选择DTO
     * @return 学生课程实体
     */
    StudentCourse stuChooseCourseDtoToStudentCourse(StuChooseCourseDTO dto);
}