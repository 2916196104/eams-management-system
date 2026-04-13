package com.zeroone.star.j5.appoint.controller;

import com.zeroone.star.j5.appoint.service.IAppointmentService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.appoint.AppointmentCalendarDTO;
import com.zeroone.star.project.j5.appoint.AppointmentApis;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import com.zeroone.star.project.query.j5.appoint.AppointmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentDetailVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
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
@RequestMapping("/j5-appoint")
@Api(tags = "预约管理")
public class AppointController implements AppointmentApis {

    @Resource
    IAppointmentService appointmentService;

    @Override
    @ApiOperation("获取预约日历（条件）")
    @GetMapping("/calendar")
    public JsonVO<List<AppointmentCalendarDTO>> queryAppointmentCalendar(@Validated AppointmentCalendarQuery appointmentCalendarQuery) {
        return JsonVO.success(appointmentService.listAppointmentCalendar(appointmentCalendarQuery));
    }

    @GetMapping
    @ApiOperation("获取预约列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AppointmentListVO>> queryPage(AppointmentQuery appointmentQuery) {
        PageDTO<AppointmentListVO> pageResult = appointmentService.queryAppointmentPage(appointmentQuery);
        return JsonVO.success(pageResult);
    }


    @GetMapping("/{id}")
    @ApiOperation("获取预约详情")
    @Override
    public JsonVO<AppointmentDetailVO> getAppointmentDetail(@PathVariable("id") Long id) {
        if (id == null) {
            return JsonVO.fail("预约ID不能为空");
        }
        AppointmentDetailVO detail = appointmentService.getAppointmentDetailById(id);
        if (detail == null) {
            return JsonVO.fail("未查询到该预约详情或数据已失效");
        }
        return JsonVO.success(detail);
    }

    @PostMapping("/confirm")
    @ApiOperation("确认预约（支持批量操作）")
    @Override
    public JsonVO<List<Long>> confirmAppointment(@RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请至少选择一条预约记录");
        }
        boolean success = appointmentService.confirmAppointments(ids);
        return success ? JsonVO.success(ids) : JsonVO.fail("确认失败，数据可能已被处理");
    }

    @PostMapping("/cancel")
    @ApiOperation("取消预约（支持批量操作）")
    @Override
    public JsonVO<List<Long>> cancelAppointment(@RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请至少选择一条预约记录");
        }
        boolean success = appointmentService.cancelAppointments(ids);
        return success ? JsonVO.success(ids) : JsonVO.fail("取消失败，数据可能已被处理");
    }
}