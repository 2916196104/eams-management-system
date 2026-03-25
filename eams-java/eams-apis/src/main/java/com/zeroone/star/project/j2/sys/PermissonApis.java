package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.j2.sys.Roleperm.PermissionDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Roleperm.PermissionGroupVO;
import io.swagger.annotations.ApiModelProperty;

import java.util.List;

public interface PermissonApis {
    /**
     * 获取可分配的权限
     * @return 可分配的权限vo
     */
    @ApiModelProperty("获取可分配的权限")
    JsonVO<PermissionGroupVO> queryPermission();
    /**
     * 根据角色id查询对应的权限
     * @param roleId 用户id
    * @return 已分配的权限vo
     */
    @ApiModelProperty("获取已分配的权限")
    JsonVO<PermissionGroupVO> querySelectedPermission(String roleId);

    /**
     * 根据角色id，先删除对应的权限，再插入已选择的权限(保存角色分配的权限)
     * @param roleId 用户id
     * @param list  勾选的权限
     * @return 是否成功
     */
    @ApiModelProperty("保存角色权限分配")
    JsonVO<Long> savePermission(String roleId,List<PermissionDTO> list);

}
     