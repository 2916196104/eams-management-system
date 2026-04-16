package com.zeroone.star.project.vo.j9.material;

import com.zeroone.star.project.dto.j9.material.MaterialDTO;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(description = "物料查询结果")
public class MaterialVO extends MaterialDTO {

    @ApiModelProperty(value = "物料启用状态", example = "1")
    private Boolean state;

    @ApiModelProperty(value = "最后编辑时间", example = "2077-1-1 00:00")
    private String editTime;
}