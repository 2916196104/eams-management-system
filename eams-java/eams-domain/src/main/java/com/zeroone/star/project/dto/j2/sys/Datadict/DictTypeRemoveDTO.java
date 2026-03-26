package com.zeroone.star.project.dto.j2.sys.Datadict;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("字典类型删除DTO")
public class DictTypeRemoveDTO {

    @ApiModelProperty("待删除的字典类型ID（必填，支持批量删除：传入ID数组）")
    private Integer[] ids;
}