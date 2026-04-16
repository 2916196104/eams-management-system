package com.zeroone.star.material.controller;


import com.zeroone.star.material.service.IMaterialRecordService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.material.MaterialRecordDTO;
import com.zeroone.star.project.j9.material.MaterialRecordApis;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import javax.validation.constraints.NotEmpty;
import java.util.List;

/**
 * <p>
 * 物料出入库记录 前端控制器
 * </p>
 *
 * @author fantast
 * @since 2026-03-16
 */
@RestController
@RequestMapping("material-record")
@Api(tags = "物料记录接口")
@Validated
public class MaterialRecordController implements MaterialRecordApis {

    @Resource
    private IMaterialRecordService materialRecordService;

    @GetMapping
    @ApiOperation("获取记录列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<MaterialRecordDTO>> queryPage(MaterialRecordQuery condition) {
        PageDTO<MaterialRecordDTO> result = materialRecordService.listPage(condition);
        return JsonVO.success(result);
    }

    @PostMapping("InStorage")
    @ApiOperation("物料入库")
    @Override
    public JsonVO<List<Long>> addInStorage(
            @ApiParam(value = "物料ID列表", required = true)
            @RequestBody List<Long> ids,
            @ApiParam(value = "入库数量，默认1", example = "1")
            @RequestParam(defaultValue = "1") Integer amount) {
        List<Long> resultIds = materialRecordService.saveInStorage(ids, amount);
        return JsonVO.success(resultIds);
    }

    @PostMapping("OutStorage")
    @ApiOperation("物料出库")
    @Override
    public JsonVO<List<Long>> addOutStorage(
            @ApiParam(value = "物料ID列表", required = true)
            @RequestBody List<Long> ids,
            @ApiParam(value = "出库数量，默认1", example = "1")
            @RequestParam(defaultValue = "1") Integer amount) {
        List<Long> resultIds = materialRecordService.saveOutStorage(ids, amount);
        return JsonVO.success(resultIds);
    }
}

