package com.zeroone.star.project.query.j4.student;
//StudentQuery: 包含姓名、电话、状态（在线/意向/结业）、顾问ID、分页参数。


import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class StudentQuery extends PointsQuery{
    @ApiModelProperty("姓名")
    private String name;
    @ApiModelProperty("电话")
    private String phone;
    @ApiModelProperty("状态")
    private String status;
    @ApiModelProperty("顾问ID")
    private String advisorId;
    @ApiModelProperty("页码")
    private Integer page;
}
