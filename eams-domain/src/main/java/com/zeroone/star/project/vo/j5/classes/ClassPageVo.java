package com.zeroone.star.project.vo.j5.classes;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel(description = "分页数据")
public class ClassPageVo<T> {
    @ApiModelProperty(value = "总记录数", example = "58")
    private Long total;
    @ApiModelProperty(value = "数据列表")
    private List<T> list;
}
