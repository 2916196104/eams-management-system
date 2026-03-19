package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.*;
import com.zeroone.star.project.dto.query.j2.sys.DictItemQuery;
import com.zeroone.star.project.j2.sys.DatadictApis;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.DatadictVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;
@RestController
@Api(tags= "数据字典")
@RequestMapping("j2-sys/dict")
public class DatadictController implements DatadictApis {
    @GetMapping
    @ApiOperation("获取字典类型名称列表")
    @Override
    public JsonVO<List<DictDTO>> query() {
        return null;
    }
    @GetMapping("/type")
    @ApiOperation("获取字典类型列表(条件+分页)")
    public JsonVO<PageDTO<DictItemDTO>> queryPage(DictItemQuery condition) {
        return null;
    }


    @PostMapping("/save-dict-type")
    @ApiOperation("保存字典类型")
    @Override
    public JsonVO<Boolean> saveDictType(@RequestBody DictTypeSaveDTO saveDTO){ return null;}

    @DeleteMapping("/remove-dict-type")
    @ApiOperation("删除字典类型")
    @Override
    public JsonVO<Boolean> removeDictType(@RequestBody DictTypeRemoveDTO removeDTO){ return null;}

    @GetMapping("/list-by-dict-id")
    @ApiOperation(value = "获取字典名称列表")
    @Override
    public JsonVO<PageDTO<DatadictVO>> listDatadictByDictIdPage(
            @NotNull(message = "字典类型ID不能为空") @RequestParam("dictId") Long dictId,
            @Valid @RequestBody PageQuery query) {
        return null;
    }

    @ApiOperation(value = "根据ID获取数据字典", notes = "根据ID获取数据字典")
    @GetMapping("/{id}")
    @Override
    public JsonVO<DatadictVO> getDatadictById(@PathVariable("id") Integer id) {
        return null;
    }

    @GetMapping
    @ApiOperation(value = "分页查询数据字典列表", notes = "分页查询数据字典列表")
    @Override
    public JsonVO<PageDTO<DatadictVO>> listDatadict(@Validated @RequestBody PageQuery query) {
        return null;
    }

    @PostMapping
    @ApiOperation(value = "保存字典", notes = "保存字典")
    @Override
    public JsonVO<String> addDatadict(@Validated @RequestBody DatadictDTO dto) {
        return null;
    }

    @PutMapping
    @ApiOperation(value = "修改字典", notes = "修改字典")
    @Override
    public JsonVO<String> updateDatadict(@Validated @RequestBody DatadictDTO dto) {
        return null;
    }

    @DeleteMapping
    @ApiOperation(value = "删除字典（支持批量）", notes = "删除字典（支持批量）")
    @Override
    public JsonVO<String> deleteDatadict(@RequestBody List<Integer> ids) {
        return null;
    }

}
