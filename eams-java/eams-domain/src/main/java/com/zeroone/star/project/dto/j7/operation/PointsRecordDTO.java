package com.zeroone.star.project.dto.j7.operation;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel("积分记录对象")
public class PointsRecordDTO {

    @ApiModelProperty("序号")
    private Long id;

    @ApiModelProperty("学生姓名")
    private String name;

    @ApiModelProperty("变动原因")
    private String reason;

    @ApiModelProperty("变动积分")
    private Long point;

    @ApiModelProperty("剩余积分")
    private Long remainPoint;

    @ApiModelProperty("说明")
    private String instruction;

    @ApiModelProperty("变动时间")
    private LocalDateTime updateTime;

}
