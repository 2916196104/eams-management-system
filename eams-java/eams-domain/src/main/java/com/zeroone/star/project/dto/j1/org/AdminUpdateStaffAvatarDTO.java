package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：管理员修改员工头像数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author chichu
 * @version 1.0.0
 */
@Data
@ApiModel("管理员修改员工头像数据传输对象")
public class AdminUpdateStaffAvatarDTO {
    @ApiModelProperty(value = "员工ID", required = true)
    private Long staffId;

    @ApiModelProperty(value = "头像URL", required = true)
    private String avatarUrl;
}