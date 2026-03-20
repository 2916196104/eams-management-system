package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.PermissionDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.RolepermDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.RolepermStaffDTO;
import com.zeroone.star.project.j2.sys.RolepermApis;
import com.zeroone.star.project.query.j2.sys.roleperm.RolepermQuery;
import com.zeroone.star.project.query.j2.sys.roleperm.RolepermStaffQuery;
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
@Api(tags = "角色权限")
public class RolepermController implements RolepermApis {

    /**
     * 负责人：小白
     */
    @Override
    @ApiOperation("获取角色名称列表（条件）")
    @GetMapping("/nameList")
    public JsonVO<List<RolepermDTO>> getNameList(RolepermQuery query) {
        return null;
    }

    @Override
    @GetMapping("/page")
    @ApiOperation("获取角色列表（条件+分页）")
    public JsonVO<List<RolepermDTO>> getPage(RolepermQuery query) {
        return null;
    }

    @Override
    @PostMapping("/save")
    @ApiOperation("保存角色")
    public JsonVO<RolepermDTO> saveRole(RolepermDTO dto) {
        return null;
    }
    /**
     * 负责人：isme
     */
    @Override
    @DeleteMapping("/delete/role/{id}")
    @ApiOperation("删除角色")
    public JsonVO<PageDTO<RolepermDTO>> removeRoleperm(RolepermQuery query) {
        return null;
    }

     /**
     * 负责人：Yaco
     */
    @Override
    @GetMapping("/query/list/permission")
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
    /**
     * 负责人：isme
     */
    @Override
    @GetMapping("/list/staff")
    @ApiOperation("获取角色员工列表（条件+分页）")
    public JsonVO<PageDTO<RolepermStaffDTO>> queryListRolepermStaff(RolepermStaffQuery query) {
        return null;
    }

    @Override
    @PostMapping("/save/staff")
    @ApiOperation("给角色添加员工")
    public JsonVO<String> addRolepermStaff(RolepermStaffDTO rolepermStaffDTO) {
        return null;
    }

    @Override
    @DeleteMapping("/delete/staff/{id}")
    @ApiOperation("从角色移除员工")
    public JsonVO<String> removeRolepermStaff(String id) {
        return null;
    }
}
