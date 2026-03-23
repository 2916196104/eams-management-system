package com.zeroone.star.j5.appoint.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.appoint.AppointmentApis;
import com.zeroone.star.project.query.j5.appoint.AppointmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentDetailVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;
import java.util.List;
/**
 * <p>
 * 预约模块controller
 * </p>
 *
 * @author makise
 * @since 2026/3/23
 */
@RestController
@RequestMapping("j5/appt")
@Api(tags = "预约管理")
public class AppointmentController implements AppointmentApis {

    @GetMapping
    @ApiOperation("获取预约列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AppointmentListVO>> queryPage(AppointmentQuery appointmentQuery) {
        return null;
    }


    @GetMapping("/{id}")
    @ApiOperation("获取预约详情")
    @Override
    public JsonVO<AppointmentDetailVO> getAppointmentDetail(@PathVariable("id") Long id) {
        return null;
    }

    @PostMapping("/confirm")
    @ApiOperation("确认预约（支持批量操作）")
    @Override
    public JsonVO<List<Long>> confirmAppointment(@RequestBody List<Long> ids) {
        return null;
    }

    @PostMapping("/cancel")
    @ApiOperation("取消预约（支持批量操作）")
    @Override
    public JsonVO<List<Long>> cancelAppointment(@RequestBody List<Long> ids) {
        return null;
    }
}