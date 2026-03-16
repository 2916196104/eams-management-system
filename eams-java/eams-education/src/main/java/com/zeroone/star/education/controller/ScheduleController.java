package com.zeroone.star.education.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.schedule.ScheduleSaveDTO;
import com.zeroone.star.project.j5.schedule.SchedulePlanApis;
import com.zeroone.star.project.query.j5.schedule.SchedulePlanQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.schedule.SchedulePlanVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
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

    @GetMapping
    @ApiOperation("获取计划列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<SchedulePlanVO>> queryPage(SchedulePlanQuery query) {
        return null;
    }

    @PostMapping
    @ApiOperation("保存计划")
    @Override
    public JsonVO<Long> saveSchedule(ScheduleSaveDTO scheduleSaveDTO) {
        return null;
    }

    @DeleteMapping
    @ApiOperation("删除计划（支持批量删除）")
    @Override
    public JsonVO<List<Long>> deleteSchedule(@RequestBody List<Long> ids) {
        return null;
    }

    @GetMapping("/{id}")
    @ApiOperation("获取计划详情")
    @Override
    public JsonVO<ScheduleSaveDTO> getScheduleById(@PathVariable Long id) {
        return null;
    }
}
