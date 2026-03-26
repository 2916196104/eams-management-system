package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 描述：跟进记录列表响应 VO
 * 注意：字段必须和 Mapper XML 中 SELECT 查询的列别名完全一致
 */
@Data
public class FollowUpVO {

    @ApiModelProperty(value = "主键ID")
    private Long id;

    @ApiModelProperty(value = "学生ID")
    private Long studentId;

    @ApiModelProperty(value = "学生姓名") // 你的 SQL 查了这个，这里必须接住
    private String studentName;

    @ApiModelProperty(value = "跟进内容")
    private String info;

    @ApiModelProperty(value = "跟进时间")
    private String contactTime;

    @ApiModelProperty(value = "下次跟进时间")
    private String contactNextTime;

    @ApiModelProperty(value = "跟进方式")
    private Integer contactType;

    @ApiModelProperty(value = "联系电话")
    private String contactPhone;

    @ApiModelProperty(value = "学生阶段")
    private Integer stage;

    @ApiModelProperty(value = "跟进人ID")
    private String creator;

    @ApiModelProperty(value = "创建时间")
    private String addTime;
}