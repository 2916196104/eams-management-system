package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：经手人数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Data
@ApiModel("经手人数据传输对象")
public class StuChooseStaffDTO extends StuChooseStaffAddDTO {
    @ApiModelProperty(value = "编号", example = "1")
    @NotNull(message = "编号不能为空")
    private Long id;
}
