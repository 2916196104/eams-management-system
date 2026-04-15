package com.zeroone.star.project.dto.j2.sys.Datadict;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("字典类型保存DTO")
public class DictTypeSaveDTO {

    @ApiModelProperty("主键ID（新增时不传，修改时传对应ID）")
    private Integer id;

    @ApiModelProperty("数据类型名称（必填）")
    private String name;

    @ApiModelProperty("字典编码")
    private String code;

    @ApiModelProperty("备注")
    private String remark;

    @ApiModelProperty("排序号")
    private String sortNum;
}
