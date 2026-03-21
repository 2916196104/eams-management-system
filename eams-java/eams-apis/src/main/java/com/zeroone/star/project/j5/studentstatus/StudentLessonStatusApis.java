package com.zeroone.star.project.j5.studentstatus;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;
import java.util.Map;

/**
 * 学员课程状态管理接口（API层定义）
 */
public interface StudentLessonStatusApis {
    /**
     * 分页查询学员课程状态列表
     */
    JsonVO<PageDTO<Map<String, Object>>> list(String keyword, String status, PageQuery query);

    /**
     * 签到保存
     */
    JsonVO<Integer> saveSign(LessonSignSaveDTO lessonSignSaveDTO);

    /**
     * 批量签到
     */
    JsonVO<Integer> batchSaveSign(List<LessonSignSaveDTO> lessonSignSaveDTOs);

    /**
     * 批量设置课程状态
     */
    JsonVO<Integer> batchSetStatus(List<Long> lessonStudentIds, String status);

    /**
     * 批量还原课程进度
     */
    JsonVO<Integer> batchRestore(List<Long> lessonStudentIds);

    /**
     * 分页查询课次变更流水
     */
    JsonVO<PageDTO<?>> queryLessonCountLog(LessonCountLogQueryDTO queryDTO);
}
