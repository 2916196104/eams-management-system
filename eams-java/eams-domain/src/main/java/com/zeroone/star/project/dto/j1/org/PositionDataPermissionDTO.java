package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.hibernate.validator.constraints.Range;

import javax.validation.constraints.NotBlank;

@ApiModel("职位数据权限DTO")
@Data
public class PositionDataPermissionDTO {

    @ApiModelProperty(value = "数据权限记录ID（新增不传，修改必传）", example = "1")
    private Long id;

    @ApiModelProperty(value = "职位ID", required = true, example = "100")
    @NotBlank(message = "职位ID不能为空")
    private Long positionId;

    @ApiModelProperty(value = "数据表表名", required = true, example = "staff")
    @NotBlank(message = "数据表表名不能为空")
    private String entityName;

    @ApiModelProperty(value = "数据权限范围类型", required = true, example = "1")
    @Range(min = 0, max = 255, message = "数据权限范围在0-255之间")
    private Integer scopeType;

    @ApiModelProperty(value = "负责人字段", example = "creator")
    private String ownerField;

    @ApiModelProperty(value = "数据所属组织字段名", example = "orgId")
    private String ownerOrgField;
}