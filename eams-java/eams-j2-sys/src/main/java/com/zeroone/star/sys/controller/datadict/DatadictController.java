package com.zeroone.star.sys.controller.datadict;

import cn.hutool.db.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.DatadictDTO;
import com.zeroone.star.project.j2.sys.DatadictApis;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.DatadictVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 描述：数据字典控制器类
 * </p>
 * @author softmaple
 * @version 1.0.0
 */
@RestController
@RequestMapping("/sys/datadict")
@Api(tags = "数据字典管理")
@Validated
public class DatadictController implements DatadictApis {

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
    @ApiOperation(value = "保存数据字典", notes = "保存数据字典")
    @Override
    public JsonVO<String> addDatadict(@Validated @RequestBody DatadictDTO dto) {
        return null;
    }

    @PutMapping
    @ApiOperation(value = "修改数据字典", notes = "修改数据字典")
    @Override
    public JsonVO<String> updateDatadict(@Validated @RequestBody DatadictDTO dto) {
        return null;
    }

    @DeleteMapping
    @ApiOperation(value = "删除数据字典", notes = "删除数据字典")
    @Override
    public JsonVO<String> deleteDatadict(@RequestBody List<Integer> ids) {
        return null;
    }
}
