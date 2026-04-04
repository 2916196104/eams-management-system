package com.zeroone.star.sys.controller;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogOperatorDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.PermissionDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.RolepermDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.RolepermStaffDTO;
import com.zeroone.star.project.j2.sys.RolepermApis;
import com.zeroone.star.project.query.j2.sys.optlog.OptlogOperatorQuery;
import com.zeroone.star.project.query.j2.sys.roleperm.RolepermQuery;
import com.zeroone.star.project.query.j2.sys.roleperm.RolepermStaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Roleperm.PermissionGroupListVO;
import com.zeroone.star.project.vo.j2.sys.Roleperm.PermissionGroupVO;
import com.zeroone.star.sys.entity.Staff;
import com.zeroone.star.sys.entity.SysPermission;
import com.zeroone.star.sys.entity.SysRole;
import com.zeroone.star.sys.entity.SysUserRole;
import com.zeroone.star.sys.mapper.StaffMapper;
import com.zeroone.star.sys.mapper.SysUserRoleMapper;
import com.zeroone.star.sys.mapper.roleperm.MsPermissionMapper;
import com.zeroone.star.sys.service.SysRoleService;
import com.zeroone.star.sys.service.roleperm.SysPermissionService;
import io.swagger.annotations.*;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.StringUtils;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * @author isme
 * @description
 * @title com.zeroone.star.sys.controller
 * @date 2026/3/16
 */
@RestController
@RequestMapping("/j2-sys/roleperm")
@Api(tags = "角色权限")
public class RolepermController implements RolepermApis {
    @Resource
    private SysUserRoleMapper sysUserRoleMapper;

    @Resource
    private StaffMapper staffMapper;
    @Resource
    private MsPermissionMapper msPermissionMapper;
    @Resource
    private SysRoleService roleService;

    @Resource
    private SysRoleService sysRoleService;
    @Resource
    private SysPermissionService PermissionService;

    /**
     * 负责人：小白
     */
    private RolepermDTO toDto(SysRole sysRole) {
        RolepermDTO dto = new RolepermDTO();
        dto.setId(sysRole.getId() == null ? null : sysRole.getId().longValue());
        dto.setName(sysRole.getName());
        dto.setCode(sysRole.getCode());
        return dto;
    }
    private SysRole toEntity(RolepermDTO dto) {
        SysRole sysRole = new SysRole();
        if (dto != null) {
            if (dto.getId() != null) sysRole.setId(dto.getId().intValue());
            sysRole.setName(dto.getName());
            sysRole.setCode(dto.getCode());
        }
        return sysRole;
    }
    @ApiOperation("获取角色名称列表（条件）")
    @GetMapping("/nameList")
    public JsonVO<List<RolepermDTO>> getNameList(RolepermQuery query) {
        QueryWrapper<SysRole> wrapper = new QueryWrapper<>();
        if (query.getName() != null) wrapper.like("name", query.getName());
        if (query.getCode() != null) wrapper.eq("code", query.getCode());
        List<SysRole> sysRoles = sysRoleService.list(wrapper);
        List<RolepermDTO> dtoList = sysRoles.stream().map(this::toDto).collect(Collectors.toList());
        return JsonVO.success(dtoList);
    }

    @ApiOperation("获取角色列表（分页＋条件）")
    @GetMapping("/page")
    public JsonVO<List<RolepermDTO>> getPage(RolepermQuery query) {
        long pageIndex = (query.getPageIndex() > 0 ? query.getPageIndex() : 1);
        long pageSize = (query.getPageSize() > 0 ? query.getPageSize() : 10);

        Page<SysRole> page = new Page<>(pageIndex, pageSize);
        QueryWrapper<SysRole> wrapper = new QueryWrapper<>();
        if (query.getName() != null) wrapper.like("name", query.getName());
        if (query.getCode() != null) wrapper.eq("code", query.getCode());
        wrapper.orderByDesc("id");

        Page<SysRole> result = sysRoleService.page(page, wrapper);
        List<RolepermDTO> dtoList = result.getRecords().stream().map(this::toDto).collect(Collectors.toList());
        return JsonVO.success(dtoList);
    }

    @ApiOperation("保存角色")
    @PostMapping("/save/role")
    public JsonVO<RolepermDTO> saveRole(RolepermDTO dto) {
        if (dto == null) {
            return JsonVO.fail("参数无效");
        }
        SysRole sysRole = toEntity(dto);
        boolean saved;
        if (dto.getId() != null) {
            saved = sysRoleService.save(sysRole);
        } else {                  //updateById()
            saved = sysRoleService.save(sysRole);
            dto.setId(sysRole.getId() == null ? null : sysRole.getId().longValue());
        }
        return saved ? JsonVO.success(dto) : JsonVO.fail("保存失败");
    }
    /**
     * 负责人：isme
     */
    @DeleteMapping("/remove/role")
    @ApiOperation("删除角色")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "roleId", value = "角色ID（推荐传此参数）", paramType = "query", dataType = "int", example = "1"),
    })
    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<PageDTO<RolepermDTO>> removeRoleperm(RolepermQuery query) {
        int roleId = query != null ? query.getId() : 0;
        if (roleId <= 0) {
            HttpServletRequest request = getRequest();
            if (request != null) {
                String roleIdStr = request.getParameter("roleId");
                if (StringUtils.hasText(roleIdStr)) {
                    try {
                        roleId = Integer.parseInt(roleIdStr);
                    } catch (NumberFormatException ignored) {
                    }
                }
                String idStr = request.getParameter("id");
                if (StringUtils.hasText(idStr)) {
                    try {
                        roleId = Integer.parseInt(idStr);
                    } catch (NumberFormatException ignored) {
                    }
                }
            }
        }
        if (roleId <= 0) {
            return JsonVO.fail("参数错误");
        }
        sysUserRoleMapper.delete(new QueryWrapper<SysUserRole>().eq("role_id", String.valueOf(roleId)));
        boolean removed = sysRoleService.removeById(roleId);
        if (!removed) {
            return JsonVO.fail("删除失败");
        }
        return JsonVO.success(null);
    }


    /**
     * 负责人：Yaco
     */

    @Override
    @GetMapping("/query/list/select/{roleId}")
    @ApiOperation("获取已分配的权限")
    public JsonVO<PermissionGroupListVO> querySelectedPermission(@PathVariable String roleId) {
        List<SysPermission> allPermissions = PermissionService.queryPermission(); // 查所有权限
        List<SysPermission> selectedPermissions = PermissionService.querySelectedPermission(roleId); // 查该角色已选权限

        // 2. 转换为 DTO
        List<PermissionDTO> allDTOs = msPermissionMapper.entitiesToDTOs(allPermissions);
        List<PermissionDTO> selectedDTOs = msPermissionMapper.entitiesToDTOs(selectedPermissions);
        Set<Long> selectedIds = selectedDTOs.stream().map(PermissionDTO::getId).collect(Collectors.toSet());

        // 3. 按分组聚合（全量权限 + 已选标记）
        Map<String, List<PermissionDTO>> groupMap = allDTOs.stream()
                .collect(Collectors.groupingBy(PermissionDTO::getGroupName));

        List<PermissionGroupVO> groupList = groupMap.entrySet().stream()
                .map(entry -> {
                    PermissionGroupVO groupVO = new PermissionGroupVO();
                    groupVO.setGroupName(entry.getKey());
                    groupVO.setPermissions(entry.getValue()); // 该分组下的所有权限
                    // 筛选该分组下的已选权限（用于前端勾选）
                    List<PermissionDTO> selectedInGroup = entry.getValue().stream()
                            .filter(p -> selectedIds.contains(p.getId()))
                            .collect(Collectors.toList());
                    groupVO.setSelectedPermissions(selectedInGroup);
                    return groupVO;
                })
                .collect(Collectors.toList());

        PermissionGroupListVO result = new PermissionGroupListVO();
        result.setGroupList(groupList);
        return JsonVO.success(result);

    }


    @Override
    @PostMapping("/modify/{roleId}")
    @ApiOperation("保存角色权限分配")
    public JsonVO<String> savePermission(
            @PathVariable @ApiParam(value = "角色ID", required = true) String roleId,
            @RequestBody List<PermissionDTO> list) {
        // 1. 参数校验
        if (roleId == null || roleId.trim().isEmpty()) {
            return JsonVO.fail("角色ID不能为空");
        }
        try {
            // 2. 转换 PermissionDTO 列表为 SysPermission 列表（只需要 id 即可）
            List<SysPermission> permissions = list.stream()
                    .map(dto -> {
                        SysPermission permission = new SysPermission();
                        permission.setId(dto.getId()); // 只需要权限ID
                        return permission;
                    })
                    .collect(Collectors.toList());
            // 3. 调用 Service 层执行保存（先删后插，带事务）
            boolean success = PermissionService.savePermission(roleId, permissions);
            // 4. 返回结果
            if (success) {
                return JsonVO.success("保存角色权限分配成功");
            } else {
                return JsonVO.fail("保存角色权限分配失败");
            }
        } catch (Exception e) {
            return JsonVO.fail("保存角色权限分配异常：" + e.getMessage());
        }
    }
    /**
     * 负责人：isme
     */
    @GetMapping("/list/staff")
    @ApiOperation("获取角色员工列表(列表+分页）")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "roleId", value = "角色ID（必传）", required = true, paramType = "query", dataType = "int", example = "1"),
    })
    @Override
    public JsonVO<PageDTO<RolepermStaffDTO>> queryListRolepermStaff(RolepermStaffQuery query) {
        if (query == null) {
            query = new RolepermStaffQuery();
        }
        Integer roleId = query.getRoleId();
        if (roleId == null || roleId <= 0) {
            HttpServletRequest request = getRequest();
            if (request != null) {
                String roleIdStr = request.getParameter("roleId");
                if (StringUtils.hasText(roleIdStr)) {
                    try {
                        roleId = Integer.parseInt(roleIdStr);
                    } catch (NumberFormatException ignored) {
                    }
                }
            }
        }
        if (roleId == null || roleId <= 0) {
            Page<RolepermStaffDTO> empty = new Page<>(1, 10);
            empty.setRecords(Collections.emptyList());
            empty.setTotal(0);
            return JsonVO.success(PageDTO.create(empty));
        }

        long pageIndex = query.getPageIndex() > 0 ? query.getPageIndex() : 1;
        long pageSize = query.getPageSize() > 0 ? query.getPageSize() : 10;
        Page<RolepermStaffDTO> page = new Page<>(pageIndex, pageSize);
        Page<RolepermStaffDTO> result = sysUserRoleMapper.selectRoleStaffPage(page, String.valueOf(roleId), query.getName());
        return JsonVO.success(PageDTO.create(result));
    }


    @PostMapping("/save/staff")
    @ApiOperation("给角色添加员工")
    @ApiImplicitParam(name = "roleId", value = "角色ID", paramType = "query", dataType = "int", example = "1")
    @Override
    public JsonVO<String> addRolepermStaff(RolepermStaffDTO rolepermStaffDTO) {
        if (rolepermStaffDTO == null || rolepermStaffDTO.getStaffId() <= 0) {
            return JsonVO.fail("参数错误");
        }
        Integer roleId = rolepermStaffDTO.getRoleId();
        if (roleId == null || roleId <= 0) {
            HttpServletRequest request = getRequest();
            if (request != null) {
                String roleIdStr = request.getParameter("roleId");
                if (StringUtils.hasText(roleIdStr)) {
                    try {
                        roleId = Integer.parseInt(roleIdStr);
                    } catch (NumberFormatException ignored) {
                    }
                }
            }
        }
        if (roleId == null || roleId <= 0) {
            return JsonVO.fail("参数错误");
        }

        if (sysRoleService.getById(roleId) == null) {
            return JsonVO.fail("角色不存在");
        }

        Long staffId = Long.valueOf(rolepermStaffDTO.getStaffId());
        Staff staff = staffMapper.selectOne(new QueryWrapper<Staff>()
                .lambda()
                .eq(Staff::getId, staffId)
                .and(w -> w.isNull(Staff::getDeleted).or().eq(Staff::getDeleted, false)));
        if (staff == null) {
            return JsonVO.fail("员工不存在");
        }

        int inserted = sysUserRoleMapper.insertRoleStaff(String.valueOf(roleId), String.valueOf(staffId));
        if (inserted <= 0) {
            return JsonVO.fail("添加失败或已存在");
        }
        return JsonVO.success("添加成功");
    }

    @DeleteMapping("/{staffId}")
    @ApiOperation("从角色移除员工")
    @ApiImplicitParam(name = "roleId", value = "角色ID（必传）", required = true, paramType = "query", dataType = "int", example = "1")
    @Override
    public JsonVO<String> removeRolepermStaff(@PathVariable("staffId") String staffId) {
        if (!StringUtils.hasText(staffId)) {
            return JsonVO.fail("参数错误");
        }
        HttpServletRequest request = getRequest();
        String roleId = request != null ? request.getParameter("roleId") : null;
        if (!StringUtils.hasText(roleId)) {
            return JsonVO.fail("参数错误");
        }
        sysUserRoleMapper.deleteByRoleIdAndUserId(roleId, staffId);
        return JsonVO.success("ok");
    }

    @GetMapping("/operators")
    @ApiOperation("获取当前所有的员工列表（姓名+职称）隐藏的接口")
    public JsonVO<PageDTO<OptlogOperatorDTO>> queryOperators(OptlogOperatorQuery query) {
        if (query == null) {
            query = new OptlogOperatorQuery();
        }
        long pageIndex = query.getPageIndex() > 0 ? query.getPageIndex() : 1;
        long pageSize = query.getPageSize() > 0 ? query.getPageSize() : 10;
        Page<OptlogOperatorDTO> page = new Page<>(pageIndex, pageSize);
        Page<OptlogOperatorDTO> result = staffMapper.selectOptlogOperators(page, query.getName());
        return JsonVO.success(PageDTO.create(result));
    }

    private HttpServletRequest getRequest() {
        ServletRequestAttributes attributes = (ServletRequestAttributes) RequestContextHolder.getRequestAttributes();
        return attributes != null ? attributes.getRequest() : null;
    }
}
