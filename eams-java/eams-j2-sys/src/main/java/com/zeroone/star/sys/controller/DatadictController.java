package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictItemDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeRemoveDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeSaveDTO;
import com.zeroone.star.project.query.j2.sys.datadict.DictItemQuery;
import com.zeroone.star.project.j2.sys.DatadictApis;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Datadict.DatadictVO;
import com.zeroone.star.sys.service.IDictItemService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import com.zeroone.star.sys.entity.Dict;
import com.zeroone.star.sys.service.DictService;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.stream.Collectors;

import javax.annotation.Resource;
import java.util.List;

@RestController
@RequestMapping("/sys/datadict")
@Api(tags = "数据字典管理")
@Validated
public class DatadictController implements DatadictApis {

    @Resource
    private IDictItemService IDictItemService;

    /**
     * 负责人：开果结苡
     */
    @Autowired
    DictService dictService;

    @GetMapping("/type-name-list")
    @ApiOperation("获取字典类型名称列表")
    @Override
    public JsonVO<List<DictDTO>> query() {
        List<Dict> dictList=dictService.list();
        List<DictDTO> dtoList = dictList.stream().map(dict -> {
            DictDTO dto = new DictDTO();
            org.springframework.beans.BeanUtils.copyProperties(dict, dto);
            return dto;
        }).collect(Collectors.toList());
        // 3. 返回结果：包装成 JsonVO
        return JsonVO.success(dtoList);
    }
    @GetMapping("/type")
    @ApiOperation("获取字典类型列表(条件+分页)")
    public JsonVO<PageDTO<DictItemDTO>> queryPage(DictItemQuery condition) {
        PageDTO<DictItemDTO> pageData = IDictItemService.queryPage(condition);
        return JsonVO.success(pageData);
    }

    /**
     * 负责人：糯擎宰2cc
     */
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
            @RequestParam("dictId") Long dictId,
            @RequestBody PageQuery query) {
        return null;
    }

    /**
     * 负责人：倾枫
     */

    @ApiOperation(value = "根据ID获取数据字典", notes = "根据ID获取数据字典")
    @GetMapping("/{id}")
    @Override
    public JsonVO<DictItemDTO> getDatadictById(@PathVariable("id") Long id) {
        DictItemDTO dictItemDTO = IDictItemService.getDatadictById(id);
        return JsonVO.success(dictItemDTO);
    }

    @GetMapping("/page")
    @ApiOperation(value = "获取字典列表（条件+分页）", notes = "分页查询数据字典列表")
    @Override
    public JsonVO<PageDTO<DatadictVO>> listDatadict(@Validated DictItemQuery query) {
        PageDTO<DatadictVO> datadictVOPageDTO = IDictItemService.listDatadictByType(query);
        return JsonVO.success(datadictVOPageDTO);
    }

    @PostMapping("/save-dict")
    @ApiOperation(value = "保存字典", notes = "添加字典")
    @Override
    public JsonVO<String> addDatadict(@Validated @RequestBody DictItemDTO dto) {
        IDictItemService.addDatadict(dto);
        return JsonVO.success(null);
    }

    @PutMapping("/update-dict")
    @ApiOperation(value = "修改字典", notes = "修改字典")
    @Override
    public JsonVO<String> updateDatadict(@Validated @RequestBody DictItemDTO dto) {
        IDictItemService.updateDatadict(dto);
        return JsonVO.success(null);
    }

    @DeleteMapping("/delete-dict")
    @ApiOperation(value = "删除字典（支持批量）", notes = "删除字典（支持批量）")
    @Override
    public JsonVO<String> deleteDatadict(@RequestBody List<Long> ids) {
        IDictItemService.deleteDatadict(ids);
        return JsonVO.success(null);
    }
}
