package com.zeroone.star.eas.controller;


import com.zeroone.star.eas.service.IGradeManagerService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.ClassGradeDto;
import com.zeroone.star.project.dto.j6.eas.GradeNameDto;
import com.zeroone.star.project.j6.eas.GradeManagerApis;
import com.zeroone.star.project.query.j6.eas.GradeManagerQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * 年级管理接口实现
 */
@RestController
@RequestMapping("/j6-eas/class_grade")
@Api(tags = "年级管理")
public class GradeManagerController implements GradeManagerApis {

    @Resource
    private IGradeManagerService gradeManagerService;

    /**
     * 获取年级列表
     *
     * @param query 查询条件
     * @return 分页数据
     */
    @GetMapping("/list")
    @ApiOperation("获取年级列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<ClassGradeDto>> queryPage(GradeManagerQuery query) {
        PageDTO<ClassGradeDto> pageResult = gradeManagerService.queryPage(query);
        return JsonVO.success(pageResult);
    }

    /**
     * 获取年级详情
     *
     * @param id 年级ID
     * @return 年级详情
     */
    @GetMapping("/{id}")
    @ApiOperation("获取年级详情")
    @Override
    public JsonVO<ClassGradeDto> getGradeById(@PathVariable("id") Long id) {
        ClassGradeDto gradeDto = gradeManagerService.getGradeById(id);
        if (gradeDto == null) {
            return JsonVO.fail("年级不存在");
        }
        return JsonVO.success(gradeDto);
    }

    /**
     * 获取年级名称列表（用于下拉框）
     *
     * @return 年级名称列表
     */
    @GetMapping("/name")
    @ApiOperation("获取年级名称列表")
    @Override
    public JsonVO<List<GradeNameDto>> QueryGradeNameList() {
        List<GradeNameDto> nameList = gradeManagerService.queryGradeNameList();
        return JsonVO.success(nameList);
    }

    /**
     * 保存年级（新增或修改）
     *
     * @param classGradeDto 年级信息
     * @return 返回年级ID
     */
    @PostMapping("/save")
    @ApiOperation("保存年级")
    @Override
    public JsonVO<Long> saveClassGrade(@RequestBody ClassGradeDto classGradeDto) {
        Long id = gradeManagerService.saveClassGrade(classGradeDto);
        return JsonVO.success(id);
    }

    /**
     * 删除年级
     *
     * @param ids 年级id列表
     * @return 删除的ID列表
     */
    @DeleteMapping("/delete")
    @ApiOperation("删除年级（支持批量删除）")
    @Override
    @ApiImplicitParam
    public JsonVO<List<Long>> deleteClassGrade(
            @ApiParam(value = "年级id列表", required = true, example = "[\"1\",\"2\"]")
            @RequestBody List<Long> ids) {
        List<Long> deletedIds = gradeManagerService.deleteClassGrade(ids);
        return JsonVO.success(deletedIds);
    }

    /**
     * 升级年级
     *
     * @param ids 年级id列表
     * @return 升级的ID列表
     */
    @PostMapping("/upgrade")
    @ApiOperation("升级年级（支持批量）")
    @Override
    public JsonVO<List<Long>> upgradeClassGrade(
            @ApiParam(value = "年级id列表", required = true, example = "[\"1\",\"2\"]")
            @RequestBody List<Long> ids) {
        List<Long> upgradedIds = gradeManagerService.upgradeClassGrade(ids);
        return JsonVO.success(upgradedIds);
    }
}
