package com.zeroone.star.eas.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.ClassGradeDto;
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
@RequestMapping("/j6/eas/class_grade")
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
    public JsonVO<PageDTO<ClassGradeDto>> queryPage(GradeManagerQuery query) {
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
    public JsonVO<ClassGradeDto> getGradeById(@PathVariable("id") Integer id) {
        return null;
    }

    /**
     * 获取年级名称列表
     */
    @GetMapping("/name")
    @ApiOperation("获取年级名称列表")
    @Override
    public JsonVO<List<ClassGradeDto>> QueryGradeNameList(@RequestParam("name") String name) {
        return null;
    }

    /**
     *
     * @param gradeManagerDto  年级信息
     * @return 返回结果
     */
    @PostMapping("/save")
    @ApiOperation("保存年级")
    @Override
    public JsonVO<Long> saveClassGrade(@RequestBody ClassGradeDto gradeManagerDto) {
        return null;
    }

    /**
     * 删除年级
     * @param ids 年级id
     * @return
     */
    @DeleteMapping("/delete")
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
    @PostMapping("/upgrade")
    @ApiOperation("升级年级（支持批量）")
    @Override
    public JsonVO<List<Long>> upgradeClassGrade(
            @ApiParam(value = "编号列表", required = true, example = "[\"1\",\"2\"]")
            @RequestBody List<Long> ids) {
        return null;
    }
}
