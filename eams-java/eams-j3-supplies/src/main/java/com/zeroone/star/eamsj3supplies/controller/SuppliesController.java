package com.zeroone.star.eamsj3supplies.controller;

import com.zeroone.star.eamsj3supplies.services.IMaterialService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialDTO;
import com.zeroone.star.project.j3.supplies.SuppliesApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

/**
 * 物料接口实现类
 */
@RestController
@RequestMapping("j3/ms")
@Api(tags = "物料管理")
public class SuppliesController implements SuppliesApis {

    @Autowired
    private IMaterialService materialService;

    @GetMapping("/getMaterial")
    @ApiOperation("获取物料列表")
    @Override
    public JsonVO<PageDTO<MaterialDTO>> getMaterial() {
        return materialService.getMaterial();
    }

    @PostMapping("/saveMaterial")
    @ApiOperation("保存/修改物料")
    @Override
    public JsonVO<MaterialDTO> saveMaterial(@RequestBody MaterialDTO materialDTO) {
        return materialService.saveMaterial(materialDTO);
    }

    @PostMapping("/deleteMaterial")
    @ApiOperation("删除物料")
    @Override
    public JsonVO<MaterialDTO> deleteMaterial(@RequestBody MaterialDTO materialDTO) {
        return materialService.deleteMaterial(materialDTO);
    }

    @PostMapping("/openMaterial")
    @ApiOperation("启用物料")
    @Override
    public JsonVO<MaterialDTO> openMaterial(@RequestBody MaterialDTO materialDTO) {
        return materialService.openMaterial(materialDTO);
    }

    @PostMapping("/closeMaterial")
    @ApiOperation("禁用物料")
    @Override
    public JsonVO<MaterialDTO> closeMaterial(@RequestBody MaterialDTO materialDTO) {
        return materialService.closeMaterial(materialDTO);
    }
}
