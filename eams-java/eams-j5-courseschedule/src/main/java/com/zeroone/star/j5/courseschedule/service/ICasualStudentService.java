package com.zeroone.star.j5.courseschedule.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.j5.courseschedule.CourseStudentDO;
import com.zeroone.star.project.dto.j5.courseschedule.CourseStudentDTO;

/**
 * @author silvan
 * @description
 */
public interface ICasualStudentService extends IService<CourseStudentDO> {
    Long addCourseStudent(CourseStudentDTO courseStudentDTO);
}
