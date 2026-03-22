package com.zeroone.star.j5.courseschedule.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.query.j5.courseschedule.StudentStatusQuery;

import java.util.List;
import java.util.Map;

public interface ILessonStudentService extends IService<LessonStudent> {

    PageDTO<Map<String, Object>> queryStatusList(StudentStatusQuery query);

    Integer addOrUpdateRecord(LessonSignSaveDTO dto);

    Integer batchAddOrUpdateRecord(List<LessonSignSaveDTO> dtoList);

    Integer batchSetStatus(List<Long> lessonStudentIds, String status);

    Integer rollbackCourseNum(List<Long> lessonStudentIds);

    PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO);

    /**
     * 停课或复课
     * @param lessonIds 课次ID列表
     * @param isResume true=复课, false=停课
     * @return 更新行数
     */
    Integer pauseOrResumeLesson(List<Long> lessonIds, Boolean isResume);
}