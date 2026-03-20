package com.zeroone.star.project.j5.courseschedule;

import com.zeroone.star.project.dto.j5.coursrschedule.CourseStatusDTO;
import com.zeroone.star.project.dto.j5.coursrschedule.LessonDTO;
import com.zeroone.star.project.dto.j5.coursrschedule.LessonListDTO;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.query.j5.courseschedule.LessonQuery;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseScheduleVO;


import java.util.List;
import java.util.Map;

public interface CourseScheduleApis {
    JsonVO<List<LessonDTO>> queryList(LessonQuery condition);

    JsonVO<PageDTO<LessonListDTO>> queryPage(LessonQuery condition);
    JsonVO<List<LessonListDTO>> queryNameList(Long id);

    //重复排课
    JsonVO<String> repeatSchedule(CourseScheduleVO lessonScheduleVo);

    //自由排课
    JsonVO<String> freeSchedule(CourseScheduleVO lessonScheduleVo);

    //开关预约课程
    JsonVO<String> switchSchedule(CourseStatusDTO couseStatusDto);

    /**
     * 分页查询学员课程状态列表
     * @param keyword 关键词
     * @param status 课程状态
     * @param query 分页参数
     * @return 分页结果
     * @author 冷月葬花魂
     */
    JsonVO<PageDTO<Map<String, Object>>> list(String keyword, String status, PageQuery query);

    /**
     * 批量设置课程状态
     * @param lessonStudentIds 课次学员记录ID列表
     * @param status 目标状态
     * @return 影响行数
     * @author 冷月葬花魂
     */
    JsonVO<Integer> batchSetStatus(List<Long> lessonStudentIds, String status);


    /**
     * 批量还原课程进度
     * @param lessonStudentIds 课次学员记录ID列表
     * @return 影响行数
     * @author 冷月葬花魂
     */
    JsonVO<Integer> batchRestore(List<Long> lessonStudentIds);

    /**
     * 停课
     * @param lessonIds 课次ID列表
     * @return 影响行数
     */
    JsonVO<Integer> stopLesson(List<Long> lessonIds);

    /**
     * 复课
     * @param lessonIds 课次ID列表
     * @return 影响行数
     */
    JsonVO<Integer> resumeLesson(List<Long> lessonIds);

}
