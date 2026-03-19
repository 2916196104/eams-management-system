package com.zeroone.star.project.j5.courseschedule;

import com.zeroone.star.project.dto.j5.coursrschedule.CourseStatusDTO;
import com.zeroone.star.project.dto.j5.coursrschedule.LessonDTO;
import com.zeroone.star.project.dto.j5.coursrschedule.LessonListDTO;
import com.zeroone.star.project.query.j5.courseschedule.LessonQuery;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseScheduleVO;


import java.util.List;

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
}
