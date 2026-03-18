package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.HolidayDTO;
import com.zeroone.star.project.j2.sys.HolidayApis;
import com.zeroone.star.project.query.j2.sys.HolidayQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

/**
 * <p>
 * 节日控制器
 * </p>
 * @author Wind
 */
@RestController
@RequestMapping("/sys/holiday")
@Api(tags = "节日管理")
public class HolidayController implements HolidayApis {
    @GetMapping
    @ApiOperation("获取已设置的节日（条件+分页）")
    @Override
    public JsonVO<PageDTO<HolidayDTO>> pageQueryHoliday(HolidayQuery query) {
        return null;
    }

    @PostMapping
    @ApiOperation("添加节日")
    @Override
    public JsonVO<String> addHoliday(HolidayDTO holidayDto) {
        return null;
    }

    @DeleteMapping("/{id}")
    @ApiOperation("删除节日")
    @Override
    public JsonVO<String> removeHoliday(@PathVariable String id) {
        return null;
    }
}
