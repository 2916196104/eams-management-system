package com.zeroone.star.project.j5.courseschedule;

import com.zeroone.star.project.dto.j5.courseschedule.*;
import com.zeroone.star.project.query.j5.courseschedule.*;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.*;
import org.springframework.web.bind.annotation.PathVariable;


import java.util.List;
import java.util.Map;

public interface CourseScheduleApis {
    JsonVO<List<LessonCalendarVO>> queryCalendar(LessonQueryDTO query);

    JsonVO<PageDTO<LessonListVO>> queryCourseList(LessonQueryDTO query);

    JsonVO<LessonDetailVO> queryCourseDetail(@PathVariable Long id);

    //重复排课
    JsonVO<String> repeatSchedule(CourseScheduleDTO courseScheduleDTO);

    //自由排课
    JsonVO<String> freeSchedule(CourseScheduleDTO courseScheduleDTO);

    //开关预约课程
    JsonVO<String> switchSchedule(CourseAppointStatusDTO courseAppointStatusDto);


    JsonVO<PageDTO<Map<String, Object>>> queryStudentsStatusList(StudentStatusQuery studentStatusQuery);
    JsonVO<Integer> batchSetStatus( SetStudentsStatusDTO setStudentsStatusDTO);
    JsonVO<Integer> batchRestore( RollBackDTO rollBackDTO);

    JsonVO<Integer> resumeLesson(CoursePauseResumeDTO coursePauseResumeDTO);


    //修改课次
    JsonVO<String> updateCourse(UpdateCourseDTO updateCourseDTO);

    //批量修改课次
    JsonVO<String> updateCourses(BatchUpdateCourseDTO batchUpdateCourseDTO);
    //删除课次
    JsonVO<String> deleteCourses(List<Long> ids);


    JsonVO<Long> saveCourseStudent(CourseStudentDTO courseStudentDTO);
    /**
     * 返回课后点评列表
     * */
    JsonVO<PageDTO<EvaluationVO>> queryPage(EvaluationQuery condition);

    /**
     * 保存点评
     * @param evaluationDTO 点评信息
     * @return 操作条数
     * */
    JsonVO<Long> saveEvaluation(EvaluationDTO evaluationDTO);


}
