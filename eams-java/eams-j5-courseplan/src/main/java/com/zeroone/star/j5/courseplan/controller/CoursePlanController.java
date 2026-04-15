package com.zeroone.star.j5.courseplan.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.github.xiaoymin.knife4j.annotations.ApiSupport;
import com.zeroone.star.j5.courseplan.service.ClassService;
import com.zeroone.star.j5.courseplan.service.CoursePlanService;
import com.zeroone.star.j5.courseplan.service.StaffService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseplan.BatchGenerateLessonDTO;
import com.zeroone.star.project.dto.j5.courseplan.ConflictCheckDTO;
import com.zeroone.star.project.dto.j5.courseplan.DeleteLessonDTO;
import com.zeroone.star.project.dto.j5.courseschedule.ScheduleSaveDTO;
import com.zeroone.star.project.j5.courseplan.CoursePlanApi;
import com.zeroone.star.project.query.j5.courseplan.SchedulePlanQuery;
import com.zeroone.star.project.query.j5.courseplan.TeacherByNameQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseplan.LessonScheduleVO;
import com.zeroone.star.project.vo.j5.courseplan.SchedulePlanVO;
import com.zeroone.star.project.vo.j5.courseplan.TeacherOptionVO;
import com.zeroone.star.project.vo.j5.courseschedule.BatchGenerateLessonVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictCheckVO;
import com.zeroone.star.project.vo.j5.courseschedule.DeleteLessonResultVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.List;

/**
 * 排课计划管理Controller
 * 实现排课计划的批量生成课表、冲突检查、删除课表等操作
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Slf4j
@RestController
@RequestMapping("/j5-course-plan")
@Api(tags = "排课计划管理", description = "排课计划的批量生成课表、冲突检查、删除课表等操作接口")
@ApiSupport(author = "j5-courseschedule", order = 1)
@Validated
public class CoursePlanController implements CoursePlanApi {
    @Resource
    private CoursePlanService coursePlanService;
    @Resource
    private ClassService classService;
    @Resource
    private StaffService staffService;



    @GetMapping("/plan/list")
    @ApiOperation("获取计划列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<SchedulePlanVO>> queryPage(SchedulePlanQuery query) {
        log.info("查询参数：{}", query); // 添加日志
        // 将page转为需要的pageDTO
        PageDTO<SchedulePlanVO> page = PageDTO.create(coursePlanService.listAll(query));
        return JsonVO.success(page);
    }



    /*
     * 保存或更新排课计划信息
     * */
    @PostMapping("/plan")
    @ApiOperation("保存计划")
    @Override
    public JsonVO<Long> saveSchedule(@RequestBody @Validated ScheduleSaveDTO scheduleSaveDTO) {
        System.out.println(">>>>>>>>>> 我收到请求了！ <<<<<<<<<<");
        return coursePlanService.saveOrUpdateSchedule(scheduleSaveDTO);
    }

    /**
     * 获取教师下拉列表
     * @param query 查询参数
     * @return 教师下拉列表
     */
    @GetMapping("/teachers")
    @ApiOperation("教师/助教下拉菜单列表")
    @Override
    public JsonVO<PageDTO<TeacherOptionVO>> getTeacherOption(TeacherByNameQuery query) {
        PageDTO<TeacherOptionVO> page = PageDTO.create(staffService.listByTeacherName(query));
        return JsonVO.success(page);
    }

    @DeleteMapping("/plan")
    @ApiOperation("删除计划（支持批量删除）")
    @Override
    public JsonVO<List<Long>> deleteSchedule(@RequestBody List<Long> ids) {
        return JsonVO.success(coursePlanService.deleteSchedule(ids));
    }

    /*
     * 根据排课计划id查询排课计划详情
     * */
    @GetMapping("/{id}")
    @ApiOperation("获取计划详情")
    @Override
    public JsonVO<LessonScheduleVO> getScheduleById(@PathVariable Long id) {
        return JsonVO.success(coursePlanService.getScheduleById(id));
    }


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
        BatchGenerateLessonVO result = coursePlanService.batchGenerateLessons(dto);
        return JsonVO.success(result);
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
        ConflictCheckVO result = coursePlanService.checkConflict(dto);
        return JsonVO.success(result);
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
        DeleteLessonResultVO result = coursePlanService.deleteLessons(dto);
        return JsonVO.success(result);
    }
}
