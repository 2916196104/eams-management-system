package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：跟进记录视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("跟进记录视图对象")
@Data
public class MyFollowVO {

    @ApiModelProperty(value = "跟进记录ID", example = "3001")
    private Long id;

    @ApiModelProperty(value = "跟进时间", example = "2024-03-15 10:30:00")
    private String followTime;

    @ApiModelProperty(value = "跟进人", example = "王老师")
    private String followerName;

    @ApiModelProperty(value = "客户（学员姓名）", example = "张三")
    private String customerName;

    @ApiModelProperty(value = "阶段", example = "1")
    private Integer stage;

    @ApiModelProperty(value = "跟进方式", example = "1")
    private Integer contactType;

    @ApiModelProperty(value = "下次跟进时间", example = "2024-03-20 14:00:00")
    private String nextFollowTime;

    @ApiModelProperty(value = "记录时间", example = "2024-03-15 10:30:00")
    private String recordTime;

    @ApiModelProperty(value = "跟进内容", example = "电话沟通课程安排")
    private String content;
}
