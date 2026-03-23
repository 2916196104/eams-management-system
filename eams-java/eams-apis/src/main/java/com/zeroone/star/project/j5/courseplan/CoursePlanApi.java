package com.zeroone.star.project.j5.courseplan;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseplan.BatchGenerateLessonDTO;
import com.zeroone.star.project.dto.j5.courseplan.ConflictCheckDTO;
import com.zeroone.star.project.dto.j5.courseplan.DeleteLessonDTO;
import com.zeroone.star.project.dto.j5.courseschedule.ScheduleSaveDTO;
import com.zeroone.star.project.query.j5.courseplan.SchedulePlanQuery;
import com.zeroone.star.project.query.j5.courseplan.TeacherByNameQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseplan.LessonScheduleVO;
import com.zeroone.star.project.vo.j5.courseplan.TeacherOptionVO;
import com.zeroone.star.project.vo.j5.courseschedule.BatchGenerateLessonVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictCheckVO;
import com.zeroone.star.project.vo.j5.courseschedule.DeleteLessonResultVO;
import com.zeroone.star.project.vo.j5.courseplan.SchedulePlanVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.validation.Valid;
import java.util.List;

/**
 * 排课计划管理API接口
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Api(tags = "排课计划管理", description = "排课计划的批量生成课表、冲突检查、删除课表等操作接口")
@RequestMapping("/api/lesson-schedule")
public interface CoursePlanApi {
    /*
     * 描述：分页查询排课计划
     * */
    JsonVO<PageDTO<SchedulePlanVO>> queryPage(SchedulePlanQuery query);



    /*
     * 描述：新增或修改排课计划
     * */
    JsonVO<Long> saveSchedule(ScheduleSaveDTO scheduleSaveDTO);

    /*
     * 描述：获取教师下拉列表
     * */
    JsonVO<PageDTO<TeacherOptionVO>> getTeacherOption(TeacherByNameQuery query);

    /*
     * 描述：删除排课计划(支持批量删除)
     * @return: 删除成功的id列表
     * */
    JsonVO<List<Long>> deleteSchedule(List<Long> ids);

    /*
     * 描述：根据id查询排课计划
     * */
    JsonVO<LessonScheduleVO> getScheduleById(Long id);




    /**
     * 批量生成课表
     *
     * @param dto 批量生成课表请求DTO
     * @return 生成结果
     */
    @ApiOperation(value = "批量生成课表", notes = "根据排课计划批量生成课表数据，包括课次、教师关联、学生关联等")
    @PostMapping("/batch-generate")
    JsonVO<BatchGenerateLessonVO> batchGenerateLessons(
            @ApiParam(value = "批量生成课表请求参数") @Valid @RequestBody BatchGenerateLessonDTO dto);

    /**
     * 冲突检查
     *
     * @param dto 冲突检查请求DTO
     * @return 冲突检查结果
     */
    @ApiOperation(value = "冲突检查", notes = "检查排课计划是否存在教师时间冲突、教室占用冲突等问题")
    @PostMapping("/conflict-check")
    JsonVO<ConflictCheckVO> checkConflict(
            @ApiParam(value = "冲突检查请求参数") @Valid @RequestBody ConflictCheckDTO dto);

    /**
     * 删除已生成课表
     *
     * @param dto 删除课表请求DTO
     * @return 删除结果
     */
    @ApiOperation(value = "删除已生成课表", notes = "删除指定排课计划生成的课表数据，包括课次、教师关联、学生关联")
    @DeleteMapping("/delete-lessons")
    JsonVO<DeleteLessonResultVO> deleteLessons(
            @ApiParam(value = "删除课表请求参数") @Valid @RequestBody DeleteLessonDTO dto);

}
