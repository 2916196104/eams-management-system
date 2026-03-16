package com.zeroone.star.eas.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.GradeManagerDto;
import com.zeroone.star.project.j6.eas.GradeManagerApis;
import com.zeroone.star.project.query.j6.eas.GradeManagerQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

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

    /**
     *
     * @param gradeManagerDto  年级信息
     * @return 返回结果
     */
    @PostMapping("/save-classgrade")
    @ApiOperation("保存职位")
    @Override
    public JsonVO<Long> saveClassGrade(@RequestBody GradeManagerDto gradeManagerDto) {
        return null;
    }

    /**
     * 删除年级
     * @param ids 年级id
     * @return
     */
    @DeleteMapping("/delete-classgrade")
    @ApiOperation("删除年级（支持批量删除）")
    @Override
    @ApiImplicitParam
    public JsonVO<List<Long>> deleteClassGrade(
            @ApiParam(value = "编号列表", required = true, example = "[\"1\",\"2\"]")
            @RequestBody List<Long> ids) {
        return null;
    }

    /**
     * 升级年级
     * @param ids 年级id
     * @return
     */
    @PostMapping("/upgrade-classgrade")
    @ApiOperation("升级年级（支持批量）")
    @Override
    public JsonVO<List<Long>> upgradeClassGrade(
            @ApiParam(value = "编号列表", required = true, example = "[\"1\",\"2\"]")
            @RequestBody List<Long> ids) {
        return null;
    }
}
