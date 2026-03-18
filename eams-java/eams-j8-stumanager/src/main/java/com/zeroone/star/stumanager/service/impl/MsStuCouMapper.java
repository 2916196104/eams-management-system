package com.zeroone.star.stumanager.service.impl;

import com.zeroone.star.project.dto.j8.SaveStu.StuSignCourseDTO;
import com.zeroone.star.project.vo.j8.StuSignCourse.StuSignCourseVO;
import com.zeroone.star.stumanager.entity.StudentCourse;
import org.mapstruct.Mapper;

import java.util.List;

/**
 * StudentCourse领域模型类型转换
 */
@Mapper(componentModel = "spring")
public interface MsStuCouMapper {


    /**
     * DO映射DTO
     * @param studentCourse 实体
     * @return DTO
     */
    StuSignCourseDTO StuSignCourseToStuSignCourseDTO(StudentCourse studentCourse);

    /**
     * DTO映射实体
     * @param stuSignCourseDTO DTO
     * @return 实体
     */
    StudentCourse StuSignCourseDTOToStuSignCourse(StuSignCourseDTO stuSignCourseDTO);


    /**
     * DTO映射VO
     * @param stuSignCourseDTO DTO
     * @return VO
     */
    StuSignCourseVO StuSignCourseDTOToStuSignCourseVO(StuSignCourseDTO stuSignCourseDTO);

    /**
     * VO映射DTO
     * @param stuSignCourseVO VO
     * @return DTO
     */
    StuSignCourseDTO StuSignCourseVOToStuSignCourseDTO(StuSignCourseVO stuSignCourseVO);

}
