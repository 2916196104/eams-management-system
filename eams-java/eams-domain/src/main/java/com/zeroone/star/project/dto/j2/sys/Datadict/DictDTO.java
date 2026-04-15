package com.zeroone.star.project.dto.j2.sys.Datadict;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("字典数据传输对象")
public class DictDTO {
    /**
     *数据id
     */
    @ApiModelProperty("主键ID")
    private  Integer id;
    /**
     * 数据名称
     */
    @ApiModelProperty("数据类型名称")
    private  String name;
    @ApiModelProperty("字典编码")
    private String code;
    @ApiModelProperty("备注")
    private  String remark;
    @ApiModelProperty("排序号")
    private  String sortNum;
}
