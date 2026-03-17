package com.zeroone.star.org.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import com.zeroone.star.project.j1.org.PositionDataPermissionApis;
import com.zeroone.star.project.query.j1.org.PositionDataPermissionQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Api(tags = "职位管理")
@RestController("j1/org")
public class PositionDataPermissionController implements PositionDataPermissionApis {

    @GetMapping("j1/org/query")
    @ApiOperation("获取职位数据权限列 表（条件+分页）")
    @Override
    public JsonVO<PageDTO<PositionDataPermissionDTO>> queryPage(PositionDataPermissionQuery condition) {
        return null;
    }

    @PostMapping("j1/org/save")
    @ApiOperation("保存职位数据权限")
    @Override
    public JsonVO<Long> addPositionDataPermission(@RequestBody PositionDataPermissionDTO positionDataPermissionDTO) {
        return null;
    }

    @DeleteMapping("j1/org/remove")
    @ApiOperation("删除职位数据权限（支持批量删除）")
    @ApiImplicitParam(name = "ids",value = "职位数据权限对应的id列表",type = "Array",required = true,example = "1")
    @Override
    public JsonVO<List<Long>> removePositionDataPermission(@RequestBody List<Long> ids) {
        return null;
    }
}
