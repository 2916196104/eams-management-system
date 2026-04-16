package com.zeroone.star.project.dto.j9.material;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

/**
 * 描述：物料数据传输对象
 */
@Data
@ApiModel("物料数据")
public class MaterialDTO {

    @ApiModelProperty(value = "物料ID（新增时不传，修改时必传）")
    private Long id;

    @NotNull(message = "物料名称不能为空")
    @ApiModelProperty(value = "物料名称", required = true, example = "笔记本")
    private String name;

    @NotNull(message = "所属学校ID不能为空")
    @ApiModelProperty(value = "所属学校ID", required = true, example = "30")
    private Long schoolId;

    @ApiModelProperty(value = "物料说明", example = "死亡笔记")
    private String info;

    @NotNull(message = "种类ID不能为空")
    @ApiModelProperty(value = "种类ID",required = true, example = "1")
    private Long categoryId;

    @ApiModelProperty(value = "物料封面图URL", example = "https://i1.hdslb.com/bfs/archive/8dd6f27e03186ef1568a924a1e7667c0ace526fa.jpg@672w_378h_1c_!web-search-common-cover.avif")
    private String cover;

    @ApiModelProperty(value = "启用状态", example = "1")
    private Boolean state;
}
