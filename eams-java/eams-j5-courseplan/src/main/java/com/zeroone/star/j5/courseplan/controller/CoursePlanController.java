package com.zeroone.star.j5.courseplan.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.github.xiaoymin.knife4j.annotations.ApiSupport;
import com.zeroone.star.project.dto.j5.courseplan.BatchGenerateLessonDTO;
import com.zeroone.star.project.dto.j5.courseplan.ConflictCheckDTO;
import com.zeroone.star.project.dto.j5.courseplan.DeleteLessonDTO;
import com.zeroone.star.project.j5.courseplan.CoursePlanApi;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.BatchGenerateLessonVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictCheckVO;
import com.zeroone.star.project.vo.j5.courseschedule.DeleteLessonResultVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

/**
 * 排课计划管理Controller
 * 实现排课计划的批量生成课表、冲突检查、删除课表等操作
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@RestController
@RequestMapping("/j5/courseplan")
@Api(tags = "排课计划管理", description = "排课计划的批量生成课表、冲突检查、删除课表等操作接口")
@ApiSupport(author = "j5-courseschedule", order = 1)
@Validated
public class CoursePlanController implements CoursePlanApi {

    /**
     * 批量生成课表
     * 根据排课计划批量生成课表数据，包括课次、教师关联、学生关联等
     */
    @Override
    @PostMapping("/batch-generate")
    @ApiOperation(
        value = "批量生成课表",
        notes = "根据排课计划批量生成课表数据，包括课次、教师关联、学生关联等。支持排除节假日、覆盖已生成课表等功能。"
    )
    @ApiOperationSupport(order = 1, author = "j5-courseschedule")
    public JsonVO<BatchGenerateLessonVO> batchGenerateLessons(
            @Valid @RequestBody BatchGenerateLessonDTO dto) {
        return null;
    }

    /**
     * 冲突检查
     * 检查排课计划是否存在教师时间冲突、教室占用冲突等问题
     */
    @Override
    @PostMapping("/conflict-check")
    @ApiOperation(
        value = "冲突检查",
        notes = "检查排课计划是否存在教师时间冲突、教室占用冲突等问题。支持按教师、教室或全部类型进行检查。"
    )
    @ApiOperationSupport(order = 2, author = "j5-courseschedule")
    public JsonVO<ConflictCheckVO> checkConflict(
            @Valid @RequestBody ConflictCheckDTO dto) {
        return null;
    }

    /**
     * 删除已生成课表
     * 删除指定排课计划生成的课表数据，包括课次、教师关联、学生关联
     */
    @Override
    @DeleteMapping("/delete-lessons")
    @ApiOperation(
        value = "删除已生成课表",
        notes = "删除指定排课计划生成的课表数据，包括课次、教师关联、学生关联。支持强制删除已签到的课次。"
    )
    @ApiOperationSupport(order = 3, author = "j5-courseschedule")
    public JsonVO<DeleteLessonResultVO> deleteLessons(
            @Valid @RequestBody DeleteLessonDTO dto) {
        // 模拟返回测试数据
        return null;
    }
}
