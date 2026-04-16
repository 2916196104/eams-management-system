package com.zeroone.star.material.controller;

import com.zeroone.star.material.service.IMaterialService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.material.MaterialDTO;
import com.zeroone.star.project.j9.material.MaterialApis;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
 * 物料管理 前端控制器
 *
 * @author fantast
 * @since 2026-03-16
 */
@RestController
@RequestMapping("material")
@Api(tags = "物料接口")
@Validated
public class MaterialController implements MaterialApis {

    @Resource
    private IMaterialService materialService;

    @GetMapping("list")
    @ApiOperation("获取物料列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<MaterialDTO>> queryAll(MaterialRecordQuery condition) {
        return JsonVO.success(materialService.listAll(condition));
    }

    @GetMapping("detail/{id}")
    @ApiOperation("获取物料详情")
    @Override
    public JsonVO<MaterialDTO> queryById(@PathVariable Long id) {
        MaterialDTO dto = materialService.getMaterialById(id);
        if (dto == null) {
            return JsonVO.fail(null);
        }
        return JsonVO.success(dto);
    }

    @PostMapping("save")
    @ApiOperation("保存物料")
    @Override
    public JsonVO<Long> addMaterial(@RequestBody MaterialDTO dto) {
        Long id = materialService.saveMaterial(dto);
        return JsonVO.success(id);
    }

    @DeleteMapping
    @ApiOperation("删除物料（支持批量删除）")
    @Override
    public JsonVO<String> removeMaterials(
            @ApiParam(value = "物料ID列表", required = true) @RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要删除的物料");
        }
        boolean success = materialService.removeByIds(ids);
        return success ? JsonVO.success("删除成功") : JsonVO.fail("删除失败");
    }

    @PutMapping("enable-disable")
    @ApiOperation("启/禁用物料")
    @Override
    public JsonVO<String> modifyMaterialState(
            @ApiParam(value = "物料ID列表", required = true)
            @RequestBody List<Long> ids,

            @ApiParam(value = "状态：0禁用 1启用", required = true)
            @RequestParam Integer state) {

        int res = materialService.updateMaterialState(ids, state);
        if (res == 1) {
            return JsonVO.success("操作成功");
        }
        return JsonVO.fail("操作失败");
    }
}
