package com.zeroone.star.project.vo.j2.sys.Roleperm;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

// 权限分组列表 VO（用于返回给前端）
@Data
@ApiModel("权限分组列表VO")
public class PermissionGroupListVO {
    @ApiModelProperty(value = "分组列表")
    private List<PermissionGroupVO> groupList;
}
