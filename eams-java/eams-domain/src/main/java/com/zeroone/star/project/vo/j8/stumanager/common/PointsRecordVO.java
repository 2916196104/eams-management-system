package com.zeroone.star.project.vo.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 积分记录展示对象
 */
@Data
@ApiModel("积分记录展示对象")
public class PointsRecordVO {
    @ApiModelProperty(value = "记录ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "学员ID", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "积分变动值", example = "10")
    private Integer credit;

    @ApiModelProperty(value = "当前积分", example = "100")
    private Integer currentCredit;

    @ApiModelProperty(value = "变动类型", example = "1")
    private Integer changeType;

    @ApiModelProperty(value = "记录来源ID", example = "3001")
    private Long sourceId;

    @ApiModelProperty(value = "操作人ID", example = "10")
    private Long staffId;

    @ApiModelProperty(value = "操作人姓名", example = "李老师")
    private String staffName;

    @ApiModelProperty(value = "变动时间", example = "2026-03-15T10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "备注", example = "活动奖励")
    private String remark;
}
