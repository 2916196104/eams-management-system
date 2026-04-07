package com.zeroone.star.j5.courseschedule.service;

import com.baomidou.mybatisplus.extension.service.*;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.*;
import io.swagger.models.auth.In;

import java.util.List;

/**
 * <p>
 * 描述：课次学员关联服务接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
public interface CourseStudentService extends IService<LessonStudent> {

    /**
     * Query lesson list with pagination.
     */
    PageDTO<?> queryList(LessonParamDTO param);

    /**
     * Batch set student status.
     */
    Integer batchSetStatus(List<Long> lessonStudentIds, String status);

    /**
     * Batch roll-call placeholder method.
     */
    Integer batchRollCall(List<LessonSignSaveDTO> signList);

    /**
     * Change lesson state in batch.
     */
    Integer changeLessonState(LessonChangeStateDTO dto);


    /**
     * Rollback consumed course count.
     */
    Integer rollbackCourseNum(List<Long> lessonStudentIds);

    /**
     * Query lesson count logs.
     */
    PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO);

    Boolean updateCourses(BatchUpdateCourseDTO batchUpdateCourseDTO);
    
    Boolean updateCourse(UpdateCourseDTO updateCourseDTO);

    Boolean deleteCourses(List<Long> ids);
}
