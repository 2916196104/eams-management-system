package com.zeroone.star.project.j5.studentstatus;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;
import java.util.Map;

/**
 * 学员课程状态管理接口（仅API层定义）
 */
public interface StudentLessonStatusApis {
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
     * 批量停课/复课
     * @param lessonStudentIds 课次学员记录ID列表
     * @param actionType 操作类型：STOP/RESUME
     * @return 影响行数
     * @author 冷月葬花魂
     */
    JsonVO<Integer> batchToggleLessonStatus(List<Long> lessonStudentIds, String actionType);

    /**
     * 批量还原课程进度
     * @param lessonStudentIds 课次学员记录ID列表
     * @return 影响行数
     * @author 冷月葬花魂
     */
    JsonVO<Integer> batchRestore(List<Long> lessonStudentIds);
}