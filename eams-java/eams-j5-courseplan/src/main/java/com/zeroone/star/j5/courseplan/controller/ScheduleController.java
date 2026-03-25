package com.zeroone.star.j5.courseplan.controller;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseplan.service.ScheduleService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.schedule.ScheduleSaveDTO;
import com.zeroone.star.project.j5.schedule.SchedulePlanApis;
import com.zeroone.star.project.query.j5.schedule.SchedulePlanQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.schedule.LessonScheduleVO;
import com.zeroone.star.project.vo.j5.schedule.SchedulePlanVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/*
* 描述：排课计划接口实现类
* */
@Slf4j
@RestController
@RequestMapping("/j5/schedule")
@Api(tags = "排课计划")
public class ScheduleController implements SchedulePlanApis {

    @Autowired
    private ScheduleService scheduleService;

    @GetMapping
    @ApiOperation("获取计划列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<SchedulePlanVO>> queryPage(SchedulePlanQuery query) {
        log.info("查询参数：{}", query); // 添加日志
        // 将page转为需要的pageDTO
        PageDTO<SchedulePlanVO> page = PageDTO.create(scheduleService.listAll(query));
        return JsonVO.success(page);
    }

    /*
     * 保存或更新排课计划信息
     * */
    @PostMapping
    @ApiOperation("保存计划")
    @Override
    public JsonVO<Long> saveSchedule(@RequestBody @Validated ScheduleSaveDTO scheduleSaveDTO) {
        System.out.println(">>>>>>>>>> 我收到请求了！ <<<<<<<<<<");
        return scheduleService.saveOrUpdateSchedule(scheduleSaveDTO);
    }

    @DeleteMapping
    @ApiOperation("删除计划（支持批量删除）")
    @Override
    public JsonVO<List<Long>> deleteSchedule(@RequestBody List<Long> ids) {
        return JsonVO.success(scheduleService.deleteSchedule(ids));
    }

    /*
    * 根据排课计划id查询排课计划详情
    * */
    @GetMapping("/{id}")
    @ApiOperation("获取计划详情")
    @Override
    public JsonVO<LessonScheduleVO> getScheduleById(@PathVariable Long id) {
        return JsonVO.success(scheduleService.getScheduleById(id));
    }
}
