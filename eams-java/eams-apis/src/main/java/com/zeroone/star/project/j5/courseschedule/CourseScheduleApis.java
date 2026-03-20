package com.zeroone.star.project.j5.courseschedule;

import com.zeroone.star.project.dto.j5.courseschedule.*;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.query.j5.courseschedule.CourseQuery;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j5.courseschedule.EvaluationQuery;
import com.zeroone.star.project.query.j5.courseschedule.UpdateCourseQuery;
import com.zeroone.star.project.query.j5.courseschedule.UpdateCoursesQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseScheduleVO;


import java.util.List;
import java.util.Map;

public interface CourseScheduleApis {
    JsonVO<List<LessonDTO>> queryList(CourseQuery condition);

    JsonVO<PageDTO<LessonListDTO>> queryPage(CourseQuery condition);
    JsonVO<List<LessonListDTO>> queryNameList(Long id);

    //重复排课
    JsonVO<String> repeatSchedule(CourseScheduleVO lessonScheduleVo);

    //自由排课
    JsonVO<String> freeSchedule(CourseScheduleVO lessonScheduleVo);

    //开关预约课程
    JsonVO<String> switchSchedule(CourseStatusDTO courseStatusDto);


    JsonVO<PageDTO<Map<String, Object>>> list(String keyword, String status, PageQuery query);
    JsonVO<Integer> batchSetStatus( List<Long> lessonStudentIds, String status);
    JsonVO<Integer> batchRestore( List<Long> lessonStudentIds);
    JsonVO<Integer> stopLesson( List<Long> lessonIds);
    JsonVO<Integer> resumeLesson(List<Long> lessonIds);


    //修改课次
    JsonVO<String> updateCourse(UpdateCourseQuery updateCourseQuery);

    //批量修改课次
    JsonVO<String> updateCourses(List<UpdateCoursesQuery> updateCoursesQueries);
    //删除课次
    JsonVO<String> deleteCourses(List<Long> ids);


    JsonVO<Long> saveCourseStudent(CourseStudentDTO courseStudentDTO);
    /**
     * 返回课后点评列表
     * */
    JsonVO<PageDTO<EvaluationDTO>> queryPage(EvaluationQuery condition);

    /**
     * 保存点评
     * @param evaluationDTO 点评信息
     * @return 操作条数
     * */
    JsonVO<Long> saveEvaluation(EvaluationDTO evaluationDTO);


}
