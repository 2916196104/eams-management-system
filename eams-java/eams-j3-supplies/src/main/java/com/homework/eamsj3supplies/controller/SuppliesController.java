package com.homework.eamsj3supplies.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialStockChangeDTO;
import com.zeroone.star.project.j3.supplies.SuppliesApis;
import com.zeroone.star.project.query.j3.supplies.MaterialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialRecordVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialStockVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import javax.annotation.Resource;
import javax.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

/**
 * 物料接口实现类
 */
@RestController
@RequestMapping("j3/ms")
@Api(tags = "物料管理")
@Validated
public class SuppliesController implements SuppliesApis {
    @Resource
    private MaterialRecordService materialRecordService;

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
    @PutMapping("/change")
    @ApiOperation("物料出入库")
    @Override
    public JsonVO<MaterialStockVO> changeMaterialAmount(@Valid @RequestBody MaterialStockChangeDTO materialStockChangeDTO) {
        return materialRecordService.changeMaterialAmount(materialStockChangeDTO);
    }

    @GetMapping("/records")
    @Override
    @ApiOperation("获取物料出入库记录列表")
    public JsonVO<PageDTO<MaterialRecordVO>> queryMaterialRecordPage(@Valid MaterialRecordQuery query) {
        return materialRecordService.queryMaterialRecordPage(query);
    }
}
