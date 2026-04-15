package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictItemDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeRemoveDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeSaveDTO;
import com.zeroone.star.project.j2.sys.DatadictApis;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.query.j2.sys.datadict.DictItemQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Datadict.DatadictVO;
import com.zeroone.star.sys.entity.Dict;
import com.zeroone.star.sys.service.datadict.DictService;
import com.zeroone.star.sys.service.datadict.DictItemService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/j2-sys/datadict")
@Api(tags = "数据字典")
@Validated
public class DatadictController implements DatadictApis {

    @Resource
    private DictItemService dictItemService;

    @Autowired
    private DictService dictService;

    /**
     * 负责人：开果结苡
     */
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
    @GetMapping("/typelist")
    @ApiOperation("获取字典类型列表(条件+分页)")
    public JsonVO<PageDTO<DictItemDTO>> queryPage(@RequestParam Long dictId,@RequestParam Integer pageIndex,@RequestParam Integer pageSize) {
        DictItemQuery  dictItemQuery=new DictItemQuery();
        dictItemQuery.setPageIndex(pageIndex);
        dictItemQuery.setPageSize(pageSize);
        dictItemQuery.setDictId(dictId);
        PageDTO<DictItemDTO> pageData = dictItemService.queryPage(dictItemQuery);
        return JsonVO.success(pageData);
    }

    /**
     * 负责人：糯擎宰2cc
     */
    @PostMapping("/save-dict-type")
    @ApiOperation("保存字典类型")
    @Override
    public JsonVO<Boolean> saveDictType(@RequestBody DictTypeSaveDTO saveDTO){
        return JsonVO.success(dictService.saveDictType(saveDTO));
    }

    @DeleteMapping("/remove-dict-type")
    @ApiOperation("删除字典类型")
    @Override
    public JsonVO<Boolean> removeDictType(@RequestBody DictTypeRemoveDTO removeDTO){
        return JsonVO.success(dictService.removeDictType(removeDTO));
    }

    @GetMapping("/list-by-dict-id")
    @ApiOperation(value = "获取字典名称列表")
    @Override
    public JsonVO<PageDTO<DatadictVO>> listDatadictByDictIdPage(
            @NotNull(message = "字典类型ID不能为空") @RequestParam("dictId") Long dictId,
            @RequestParam("pageIndex") Integer pageIndex,
            @RequestParam("pageSize") Integer pageSize) {

        return JsonVO.success(dictItemService.listDatadictByDictIdPage(dictId, pageIndex, pageSize));
    }


    /**
     * 负责人：倾枫
     */

    @ApiOperation(value = "根据ID获取数据字典", notes = "根据ID获取数据字典")
    @GetMapping("/{id}")
    @Override
    public JsonVO<DictItemDTO> getDatadictById(@PathVariable("id") Long id) {
        DictItemDTO dictItemDTO = dictItemService.getDatadictById(id);
        return JsonVO.success(dictItemDTO);
    }

    @GetMapping("/page")
    @ApiOperation(value = "获取字典列表（条件+分页）", notes = "分页查询数据字典列表")
    @Override
    public JsonVO<PageDTO<DatadictVO>> listDatadict(@Validated DictItemQuery query) {
        PageDTO<DatadictVO> datadictVOPageDTO = dictItemService.listDatadictByType(query);
        return JsonVO.success(datadictVOPageDTO);
    }

    @PostMapping("/save-dict")
    @ApiOperation(value = "保存字典", notes = "添加字典")
    @Override
    public JsonVO<String> addDatadict(@Validated @RequestBody DictItemDTO dto) {
        dictItemService.addDatadict(dto);
        return JsonVO.success(null);
    }

    @PutMapping("/update-dict")
    @ApiOperation(value = "修改字典", notes = "修改字典")
    @Override
    public JsonVO<String> updateDatadict(@Validated @RequestBody DictItemDTO dto) {
        dictItemService.updateDatadict(dto);
        return JsonVO.success(null);
    }

    @DeleteMapping("/delete-dict")
    @ApiOperation(value = "删除字典（支持批量）", notes = "删除字典（支持批量）")
    @Override
    public JsonVO<String> deleteDatadict(@RequestBody List<Long> ids) {
        dictItemService.deleteDatadict(ids);
        return JsonVO.success(null);
    }
}
