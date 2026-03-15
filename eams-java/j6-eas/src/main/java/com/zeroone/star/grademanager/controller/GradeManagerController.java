package com.zeroone.star.grademanager.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.GradeManagerDto;
import com.zeroone.star.project.j6.eas.GradeManagerApis;
import com.zeroone.star.project.query.j6.eas.GradeManagerQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.checkerframework.checker.units.qual.A;
import org.springframework.boot.actuate.endpoint.web.annotation.RestControllerEndpoint;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * 年级管理接口实现
 */
@RestController
@RequestMapping("/j6/eas")
@Api(tags = "年级管理")
public class GradeManagerController implements GradeManagerApis {
    /**
     * 获取年级列表
     *
     * @param query
     * @return
     */
    @GetMapping
    @ApiOperation("获取年级列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<GradeManagerDto>> queryPage(GradeManagerQuery query) {
        return null;
    }

    /**
     * 获取年级详情
     *
     * @param id
     */
    @GetMapping("/{id}")
    @ApiOperation("获取年级详情")
    @Override
    public JsonVO<GradeManagerDto> getGradeById(@PathVariable("id") Integer id) {
        return null;
    }

    /**
     * 获取年级名称列表
     */
    @GetMapping("/name")
    @ApiOperation("获取年级名称列表")
    @Override
    public JsonVO<List<GradeManagerDto>> QueryGradeNameList(@RequestParam("name") String name) {
        return null;
    }


}
