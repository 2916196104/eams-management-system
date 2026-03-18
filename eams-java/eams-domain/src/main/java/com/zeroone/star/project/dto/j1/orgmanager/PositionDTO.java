package com.zeroone.star.project.dto.j1.orgmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotBlank;

/**
 * <p>
 * 描述：职位数据对象
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("职位数据对象")
public class PositionDTO {
    @ApiModelProperty(value = "职位ID", notes = "新增时可不传，修改时必传", example = "1813456789012345678")
    private Long id;

    @NotBlank(message = "职位名称不能为空")
    @ApiModelProperty(value = "职位名称", required = true, example = "校长")
    private String name;
}
