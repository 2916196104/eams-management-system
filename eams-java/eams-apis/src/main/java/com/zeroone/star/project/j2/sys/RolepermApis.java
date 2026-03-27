package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogOperatorDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.PermissionDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.RolepermDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.RolepermStaffDTO;
import com.zeroone.star.project.query.j2.sys.roleperm.RolepermQuery;
import com.zeroone.star.project.query.j2.sys.roleperm.RolepermStaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Roleperm.PermissionGroupListVO;
import com.zeroone.star.project.vo.j2.sys.Roleperm.PermissionGroupVO;
import io.swagger.annotations.ApiModelProperty;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;

/**
 * @author isme
 * @description
 * @title com.zeroone.star.project.j2.sys
 * @date 2026/3/16
 */
public interface RolepermApis {
    /**
     * 角色名称列表查询
     * @param query 角色查询对象
     * @return 角色名称列表
     */
    JsonVO<List<RolepermDTO>> getNameList(RolepermQuery query);

    /**
     * 角色分页查询
     * @param query 角色查询对象
     * @return 角色分页列表
     */
    JsonVO<List<RolepermDTO>> getPage(RolepermQuery query);

    /**
     * 保存角色
     * @param dto 角色数据
     * @return 保存结果
     */
    JsonVO<RolepermDTO> saveRole(@RequestBody RolepermDTO dto);
    /**
     * 角色权限删除
     * @param query 角色权限查询对象
     * @return 删除结果
     */
    JsonVO<PageDTO<RolepermDTO>> removeRoleperm(@RequestBody RolepermQuery query);
    /**
     * 角色管理的员工列表查询
     * @param query 查询条件
     * @return 角色权限员工列表
     */
    JsonVO<PageDTO<RolepermStaffDTO>> queryListRolepermStaff(RolepermStaffQuery query);
    /**
     * 角色管理的员工新增
     * @param rolepermStaffDTO 新增数据
     * @return 新增结果
     */
    JsonVO<String> addRolepermStaff(RolepermStaffDTO rolepermStaffDTO);
    /**
     * 角色管理的员工删除
     * @param id 要删除数据的编号
     * @return 删除结果
     */
    JsonVO<String> removeRolepermStaff(String id);

    /**
     * 根据角色id查询对应的权限
     * @param roleId 用户id
     * @return 已分配的权限vo
     */
    @ApiModelProperty("获取已分配的权限")
    JsonVO<PermissionGroupListVO> querySelectedPermission(String roleId);
    /**
     * 根据角色id，先删除对应的权限，再插入已选择的权限(保存角色分配的权限)，调用deletePermission和updataPermission
     * @param roleId 用户id
     * @param list  勾选的权限
     * @return 是否勾选
     */
    @ApiModelProperty("保存角色权限分配")
    JsonVO<String> savePermission(String roleId, List<PermissionDTO> list);

}
