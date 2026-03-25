package com.zeroone.star.project.j8.stumanager.common;
import com.zeroone.star.project.dto.j8.stumanager.CourseStatisticsDTO;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.Parameter;
import io.swagger.v3.oas.annotations.tags.Tag;
import org.springframework.web.bind.annotation.*;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.ClassScheduleVO;
import com.zeroone.star.project.vo.j8.stumanager.StuClassVO;

import java.time.LocalDate;
/**
 * 班级与课表接口（API契约层）
 * 包含：加入班级、退出班级、课程统计
 *
 * @author 不想加班1
 */
@Tag(name = "班级课表管理接口", description = "提供班级加入、退出、课程统计功能")
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
    @Operation(summary = "学生加入班级", description = "学生绑定到指定班级，需校验班级/学生是否存在、是否已加入")
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
    @Operation(summary = "学生退出班级", description = "学生解除与班级的绑定，需校验是否存在绑定关系")
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
    @Operation(summary = "班级课程统计", description = "统计指定班级的课程名称、代码、课时、教师等信息")
    @GetMapping("/statistics")
    JsonVO<CourseStatisticsDTO> courseStatistics(
            @RequestParam(required = false) Long classId
    );
}