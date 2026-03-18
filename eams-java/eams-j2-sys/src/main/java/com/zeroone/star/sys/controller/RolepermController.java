package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.RolepermDTO;
import com.zeroone.star.project.dto.j2.sys.RolepermStaffDTO;
import com.zeroone.star.project.j2.sys.RolepermApis;
import com.zeroone.star.project.query.j2.sys.RolepermQuery;
import com.zeroone.star.project.query.j2.sys.RolepermStaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

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
    @DeleteMapping
    @ApiOperation("删除角色")
    @Override
    public JsonVO<PageDTO<RolepermDTO>> removeRoleperm(RolepermQuery query) {
        return null;
    }

    @GetMapping
    @ApiOperation("获取角色员工列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<RolepermStaffDTO>> queryListRolepermStaff(RolepermStaffQuery query) {
        return null;
    }
    @PostMapping
    @ApiOperation("给角色添加员工")
    @Override
    public JsonVO<String> addRolepermStaff(RolepermStaffDTO rolepermStaffDTO) {
        return null;
    }

    @DeleteMapping("/{id}")
    @ApiOperation("从角色移除员工")
    @Override
    public JsonVO<String> removeRolepermStaff(String id) {
        return null;
    }
}
