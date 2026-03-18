package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.PermissionDTO;
import com.zeroone.star.project.dto.j2.sys.RolepermDTO;
import com.zeroone.star.project.dto.j2.sys.RolepermStaffDTO;
import com.zeroone.star.project.j2.sys.RolepermApis;
import com.zeroone.star.project.query.j2.sys.RolepermQuery;
import com.zeroone.star.project.query.j2.sys.RolepermStaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Roleperm.PermissionGroupVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * @author isme
 * @description
 * @title com.zeroone.star.sys.controller
 * @date 2026/3/16
 */
@RestController
@RequestMapping("/sys/roleperm")
@Api(tags = "角色与权限")
public class RolepermController implements RolepermApis {


    @Override
    @ApiOperation("获取角色名称列表")
    @GetMapping("/nameList")
    public JsonVO<List<RolepermDTO>> getNameList(RolepermQuery query) {
        return null;
    }

    @Override
    @GetMapping("/page")
    @ApiOperation("获取角色分页列表")
    public JsonVO<List<RolepermDTO>> getPage(RolepermQuery query) {
        return null;
    }

    @Override
    @PostMapping("/save")
    @ApiOperation("保存角色")
    public JsonVO<RolepermDTO> saveRole(RolepermDTO dto) {
        return null;
    }

    @Override
    @DeleteMapping("/{id}")
    @ApiOperation("删除角色")
    public JsonVO<PageDTO<RolepermDTO>> removeRoleperm(RolepermQuery query) {
        return null;
    }


    @Override
    @ApiModelProperty("获取可分配的权限")
    public JsonVO<PermissionGroupVO> queryPermission() {
        return null;
    }

    @Override
    @GetMapping("/query/list/select/{roleId}")
    @ApiOperation("获取已分配的权限")
    public JsonVO<PermissionGroupVO> querySelectedPermission(@PathVariable String roleId) {
        return null;
    }


    @Override
    @PostMapping("/modify/{roleId}")
    @ApiOperation("保存角色权限分配")
    public JsonVO<Long> savePermission(
            @PathVariable @ApiParam(value = "角色ID", required = true) String roleId,
            @RequestBody List<PermissionDTO> list) {
        return null;
    }
    @Override
    @GetMapping
    @ApiOperation("获取角色员工列表（条件+分页）")
    public JsonVO<PageDTO<RolepermStaffDTO>> queryListRolepermStaff(RolepermStaffQuery query) {
        return null;
    }

    @Override
    @PostMapping
    @ApiOperation("给角色添加员工")
    public JsonVO<String> addRolepermStaff(RolepermStaffDTO rolepermStaffDTO) {
        return null;
    }

    @Override
    @DeleteMapping("/{id}")
    @ApiOperation("从角色移除员工")
    public JsonVO<String> removeRolepermStaff(String id) {
        return null;
    }
}
