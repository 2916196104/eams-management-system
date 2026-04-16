package com.zeroone.star.project.j8.stumanager.common;
import com.zeroone.star.project.dto.j8.stumanager.CourseStatisticsDTO;
import com.zeroone.star.project.query.j8.stumanager.common.LessonCountRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.common.LessonCountRecordVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.j8.stumanager.ClassScheduleVO;
import com.zeroone.star.project.vo.j8.stumanager.StuClassVO;

import java.time.LocalDate;
/**
 * 班级与课表接口（API契约层）
 * 包含：加入班级、退出班级、课程统计
 *
 * @author 不想加班1
 */
@Api(tags = "班级课表管理接口")
@RequestMapping("/stumanager/class")
public interface ClassScheduleApis {
    JsonVO<PageDTO<StuClassVO>> queryStuClass(Integer pageNo, Integer pageSize, Long studentId);
    JsonVO<PageDTO<ClassScheduleVO>> queryClassSchedule(Integer page, Integer pageSize, Long studentId, LocalDate beginTime, LocalDate endTime);

    /**
     * 学生加入班级
     *
     * @param studentId 学生ID
     * @param classId   班级ID
     * @return 统一返回结果
     */
    @ApiOperation(value = "学生加入班级")
    @PostMapping("/join")
    JsonVO<Void> joinClass(
            @RequestParam Long studentId,
            @RequestParam Long classId
    );

    /**
     * 学生退出班级
     *
     * @param studentId 学生ID
     * @return 统一返回结果
     */
    @ApiOperation(value = "学生退出班级")
    @PostMapping("/exit")
    JsonVO<Void> exitClass(
            @RequestParam Long studentId
    );

    /**
     * 班级课程统计
     *
     * @param classId 班级ID（可选，为空则统计所有班级）
     * @return 课程统计结果
     */
    @ApiOperation(value = "班级课程统计")
    @GetMapping("/statistics")
    JsonVO<CourseStatisticsDTO> courseStatistics(
            @RequestParam(required = false) Long classId
    );

    /**
     * 获取消课记录
     * @param query 查询条件
     * @return 消课记录分页列表
     */
    JsonVO<PageDTO<LessonCountRecordVO>> queryLessonCountRecords(LessonCountRecordQuery query);
}