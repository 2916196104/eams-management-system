package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j8.stumanager.common.ClassScheduleApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.ClassScheduleVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import com.zeroone.star.project.vo.j8.stumanager.StuClassVO;

import javax.validation.constraints.NotNull;
import java.time.LocalDate;

/**
 * 班级与课表
 */
@RequestMapping("/common")
@RestController
@Api(tags = "ClassSchedule")
public class ClassScheduleController implements ClassScheduleApis {
    @Override
    @ApiOperation(value = "查询班级列表")
    @GetMapping("/class/list")
    public JsonVO<PageDTO<StuClassVO>> queryStuClass(
            @RequestParam(defaultValue = "1") Integer pageNo,
            @RequestParam(defaultValue = "10")Integer pageSize,
            @NotNull @RequestParam String studentId) {
        return null;
    }

    @GetMapping("/lession/list")
    @ApiOperation(value = "查询课表")
    @Override
    public JsonVO<PageDTO<ClassScheduleVO>> queryClassSchedule(
                                                   @RequestParam(defaultValue = "1") Integer page,
                                                   @RequestParam(defaultValue = "10") Integer pageSize,
                                                   @NotNull @RequestParam Long studentId,
                                                   @RequestParam(required = false) LocalDate beginTime,
                                                   @RequestParam(required = false) LocalDate endTime) {
        return null;
    }

}
