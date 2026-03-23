package com.zeroone.star.project.dto.j1.orgmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：设置员工职位对象
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("设置员工职位对象")
public class PositionSetDTO {
    @ApiModelProperty(value = "创建人", example = "10001")
    private Long creator;

    @NotNull(message = "组织ID不能为空")
    @ApiModelProperty(value = "组织ID", required = true, example = "1")
    private Long orgId;

    @NotNull(message = "职位ID不能为空")
    @ApiModelProperty(value = "职位ID", required = true, example = "1")
    private Long positionId;

    @NotNull(message = "员工ID不能为空")
    @ApiModelProperty(value = "员工ID", required = true, example = "20001")
    private Long staffId;
}
