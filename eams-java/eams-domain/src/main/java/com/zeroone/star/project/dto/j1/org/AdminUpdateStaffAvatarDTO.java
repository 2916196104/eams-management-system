package com.zeroone.star.project.dto.j1.org;

import lombok.Data;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

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
public class AdminUpdateStaffAvatarDTO {
    @NotNull(message = "员工ID不能为空")
    private Long staffId;

    @NotBlank(message = "头像URL不能为空")
    private String avatarUrl;
}