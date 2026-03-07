package com.zeroone.star.sample.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.sample.SampleAddDTO;
import com.zeroone.star.project.dto.sample.SampleDTO;
import com.zeroone.star.project.query.sample.SampleQuery;
import com.zeroone.star.project.sample.SampleApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.sample.entity.Sample;
import com.zeroone.star.sample.service.ISampleService;
import com.zeroone.star.sample.service.impl.MsSampleMapper;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 演示示例表 前端控制器
 * </p>
 * @author 阿伟
 * @since 2026-03-07
 */
@RestController
@RequestMapping("/sample")
@Api(tags = "sample")
@Validated
public class SampleController implements SampleApis {

    @Resource
    ISampleService service;

    @Resource
    MsSampleMapper msSampleMapper;

    @PostMapping
    @ApiOperation(value = "添加示例")
    @Override
    public JsonVO<String> addSample(@Validated @RequestBody SampleAddDTO addDto) {
        Sample sample = msSampleMapper.addDtoToDo(addDto);
        if (service.save(sample)) {
            return JsonVO.success(sample.getId());
        }
        return JsonVO.fail(null);
    }

    @PutMapping
    @ApiOperation(value = "修改示例")
    @Override
    public JsonVO<String> modifySample(@Validated @RequestBody SampleDTO dto) {
        if (service.updateById(msSampleMapper.dtoToDo(dto))) {
            return JsonVO.success(dto.getId());
        }
        return JsonVO.fail(null);
    }

    @GetMapping
    @ApiOperation(value = "查询所有示例")
    @Override
    public JsonVO<PageDTO<SampleDTO>> queryAll(@Validated SampleQuery condition) {
        return JsonVO.success(service.listAll(condition));
    }

    @GetMapping("/{id}")
    @ApiOperation(value = "查询指定id的示例")
    @ApiImplicitParam(name = "id", value = "编号", required = true, example = "1")
    @Override
    public JsonVO<SampleDTO> queryById(@PathVariable String id) {
        return JsonVO.success(service.getById(id));
    }

    @DeleteMapping
    @ApiOperation(value = "删除示例")
    @Override
    public JsonVO<List<String>> removeSample(
            @ApiParam(value = "编号列表", required = true, example = "[\"1\",\"2\"]")
            @RequestBody List<String> ids) {
        if (service.removeByIds(ids)) {
            return JsonVO.success(ids);
        }
        return JsonVO.fail(null);
    }
}

