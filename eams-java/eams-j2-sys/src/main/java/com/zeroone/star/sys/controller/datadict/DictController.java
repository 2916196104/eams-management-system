package com.zeroone.star.sys.controller.datadict;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.DictDTO;
import com.zeroone.star.project.dto.j2.sys.DictItemDTO;
import com.zeroone.star.project.dto.j2.sys.DictTypeRemoveDTO;
import com.zeroone.star.project.dto.j2.sys.DictTypeSaveDTO;
import com.zeroone.star.project.dto.query.j2.sys.DictItemQuery;
import com.zeroone.star.project.j2.sys.DictApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;
@RestController
@Api(tags= "数据字典接口")
@RequestMapping("j2-sys/dict")
public class DictController implements DictApis {
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
}
