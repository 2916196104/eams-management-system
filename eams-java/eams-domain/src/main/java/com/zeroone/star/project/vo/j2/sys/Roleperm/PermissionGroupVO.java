package com.zeroone.star.project.vo.j2.sys.Roleperm;

import com.zeroone.star.project.dto.j2.sys.Roleperm.PermissionDTO;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel("权限分组VO")
public class PermissionGroupVO {

    @ApiModelProperty("分组名称")
    private String groupName;
    @ApiModelProperty("该分组下的权限列表")
    private List<PermissionDTO> permissions;
    @ApiModelProperty("该分组下已经选中的权限列表")
    private List<PermissionDTO> selectedPermissions;
}
