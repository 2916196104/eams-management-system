package com.zeroone.star.project.dto.j2.sys;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("字典数据类型传输对象")
public class DictItemDTO {
    @ApiModelProperty("主键ID")
    private  Integer id;
    @ApiModelProperty("字典ID")
    private  Integer dictId;
    @ApiModelProperty("数据类型列表名称")
    private  String name;
    @ApiModelProperty("描述/信息")
    private  String info;
    @ApiModelProperty("排序号")
    private  Integer sortNum;
}
