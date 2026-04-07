package com.zeroone.star.eamsj3data.controller;

import com.zeroone.star.project.dto.j3.data.CourseHistoryTotalDTO;
import com.zeroone.star.project.dto.j3.data.SignUpTrendDTO;
import com.zeroone.star.project.j3.data.SalesStatisticApi;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.annotations.ApiOperation;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.time.LocalDateTime;
import java.util.List;

@RestController
@RequestMapping("j3-statis")
@Api(tags = "销售统计")
public class SalesStatisticController implements SalesStatisticApi {

    @ApiOperation("报名趋势,默认是本月")
    @GetMapping("/courseSaleByDay")
    @Override
    public JsonVO<List<SignUpTrendDTO>> courseSaleByDay(
            @RequestParam(required = false) @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDateTime startDate,
            @RequestParam(required = false) @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDateTime endDate) {
        return null;
    }

    @ApiModelProperty("课程历史总销量，默认是全部")
    @GetMapping("/courseSalesTotal")
    @Override
    public JsonVO<List<CourseHistoryTotalDTO>> courseSalesTotal(
            @RequestParam(required = false) @DateTimeFormat LocalDateTime startDate,
            @RequestParam(required = false) @DateTimeFormat LocalDateTime endDate) {
        return null;
    }
}
