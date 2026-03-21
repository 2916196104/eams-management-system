package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel("我的跟进DTO")
public class MyFollowUpDTO {

    @ApiModelProperty(value = "主键ID")
    private Long id;

    @ApiModelProperty(value = "客户ID")
    private Long studentId;

    @ApiModelProperty(value = "客户名称")
    private String studentName;

    @ApiModelProperty(value = "阶段值")
    private Integer stage;

    @ApiModelProperty(value = "阶段名称")
    private String stageName;

    @ApiModelProperty(value = "跟进方式值")
    private Integer contactType;

    @ApiModelProperty(value = "跟进方式名称")
    private String contactTypeName;

    @ApiModelProperty(value = "跟进时间")
    private LocalDateTime contactTime;

    @ApiModelProperty(value = "下次跟进")
    private LocalDateTime contactNextTime;

    @ApiModelProperty(value = "记录时间")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "跟进内容")
    private String info;

    @ApiModelProperty(value = "联系电话")
    private String contactPhone;
}
