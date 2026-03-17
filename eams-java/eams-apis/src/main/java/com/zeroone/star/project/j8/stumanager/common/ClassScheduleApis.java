package com.zeroone.star.project.j8.stumanager.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.ClassScheduleVO;
import com.zeroone.star.project.vo.j8.stumanager.StuClassVO;

import java.time.LocalDate;

/**
 * 班级与课表
 */
public interface ClassScheduleApis {
    JsonVO<PageDTO<StuClassVO>> queryStuClass(Integer pageNo, Integer pageSize, String studentId);
    JsonVO<PageDTO<ClassScheduleVO>> queryClassSchedule(Integer page, Integer pageSize, Long studentId, LocalDate beginTime, LocalDate endTime);
}
