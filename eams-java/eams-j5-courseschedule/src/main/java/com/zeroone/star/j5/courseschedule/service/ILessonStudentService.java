package com.zeroone.star.j5.courseschedule.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.query.PageQuery;

import java.util.List;
import java.util.Map;

/**
 * <p>
 * 描述：课次学员关联服务接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
public interface ILessonStudentService extends IService<LessonStudent> {

    /**
     * Query student lesson status list.
     */
    PageDTO<Map<String, Object>> queryStatusList(String keyword, String status, PageQuery query);

    /**
     * Save one sign record.
     */
    Integer addOrUpdateRecord(LessonSignSaveDTO dto);

    /**
     * Save sign records in batch.
     */
    Integer batchAddOrUpdateRecord(List<LessonSignSaveDTO> dtoList);

    /**
     * Batch set student status.
     */
    Integer batchSetStatus(List<Long> lessonStudentIds, String status);

    /**
     * Batch toggle lesson state.
     */
    Integer batchToggleLessonStatus(List<Long> lessonStudentIds, String actionType);

    /**
     * Rollback consumed course count.
     */
    Integer rollbackCourseNum(List<Long> lessonStudentIds);

    /**
     * Query lesson count logs.
     */
    PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO);
}
