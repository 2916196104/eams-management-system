package com.zeroone.star.sys.controller;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Holiday.HolidayDTO;
import com.zeroone.star.project.j2.sys.HolidayApis;
import com.zeroone.star.project.query.j2.sys.HolidayQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.sys.entity.Holiday;
import com.zeroone.star.sys.service.IHolidayService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.time.LocalDateTime;


@RestController
@Api(tags = "节日管理")
@RequestMapping("/j2-sys/holiday")
public class HolidayController implements HolidayApis {

    @Autowired
    private IHolidayService holidayService;


    @GetMapping("/list")
    @ApiOperation("获取已设置的节日(条件 + 分页)")
    @Override
    public JsonVO<PageDTO<HolidayDTO>> pageQueryHoliday(
            @ApiParam(value = "节日查询参数", hidden = true) HolidayQuery query) {
        Page<Holiday> page = new Page<>(query.getPageIndex(), query.getPageSize());

        QueryWrapper<Holiday> queryWrapper = new QueryWrapper<>();

        if (query.getHolidayList() != null && !query.getHolidayList().isEmpty()) {
            queryWrapper.and(wrapper -> {
                for (Integer year : query.getHolidayList()) {
                    LocalDate startOfYear = LocalDate.of(year, 1, 1);
                    LocalDate endOfYear = LocalDate.of(year, 12, 31);
                    wrapper.or().between("date", startOfYear, endOfYear);
                }
            });
        }

        queryWrapper.orderByDesc("id");

        Page<Holiday> resultPage = holidayService.page(page, queryWrapper);

        PageDTO<HolidayDTO> pageDTO = PageDTO.create(resultPage, src -> {
            HolidayDTO dto = new HolidayDTO();
            dto.setId(src.getId());
            dto.setHolidayTime(src.getDate());
            return dto;
        });

        return JsonVO.success(pageDTO);
    }


@PostMapping("/add/{holidayTime}")
    @ApiOperation("添加节日")
    @Override
    public JsonVO<String> addHoliday(
            @ApiParam(value = "节日日期", required = true, example = "2026-03-15")
            @PathVariable("holidayTime")
            @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate holidayTime) {
        if (holidayTime == null) {
            return JsonVO.fail("节日时间不能为空");
        }

        QueryWrapper<Holiday> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("date", holidayTime);

        Holiday existHoliday = holidayService.getOne(queryWrapper);
        if (existHoliday != null) {
            return JsonVO.fail("该日期已存在节日，无法重复添加");
        }

        Holiday holiday = new Holiday();
        holiday.setDate(holidayTime);
        holiday.setAddTime(LocalDateTime.now());

        boolean success = holidayService.save(holiday);

        if (success) {
            return JsonVO.success("添加成功");
        } else {
            return JsonVO.fail("添加失败");
        }
    }


@DeleteMapping("/delete/{id}")
    @ApiOperation("删除节日")
    public JsonVO<String> removeHoliday(
            @ApiParam(value = "节日ID", required = true, example = "1")
            @PathVariable("id") Long id) {
        if (id == null) {
            return JsonVO.fail("节日ID不能为空");
        }

        boolean success = holidayService.removeById(id);

        if (success) {
            return JsonVO.success("删除成功");
        } else {
            return JsonVO.fail("删除失败");
        }
    }
}

