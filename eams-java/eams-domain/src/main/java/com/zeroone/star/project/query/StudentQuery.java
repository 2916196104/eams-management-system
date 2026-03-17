package com.zeroone.star.project.query;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(value = "StudentQuery", description = "学员列表查询条件")
public class StudentQuery {
    @ApiModelProperty(value = "页码", example = "1")
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页条数", example = "10")
    private Integer pageSize = 10;

    @ApiModelProperty(value = "id", example = "1")
    private Long id;

    @ApiModelProperty(value = "学员姓名", example = "小明")
    private String name;

}