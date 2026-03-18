package com.zeroone.star.project.dto.j4.student;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：跟进记录传输对象 (对应 contact_record 表)
 */
@Data
public class FollowUpDTO {

    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "学生id", required = true, example = "2008418408985583617")
    private Long studentId;

    @ApiModelProperty(value = "学员姓名 (只读/展示用，非表字段)", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "跟进记录 (对应表字段 info)", required = true, example = "沟通良好，此人意向强烈")
    private String info;

    @ApiModelProperty(value = "联系时间 (对应表字段 contact_time)", required = true, example = "2026-03-18 00:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private LocalDateTime contactTime;

    @ApiModelProperty(value = "下次联系时间 (对应表字段 contact_next_time)", example = "2026-03-18 12:51:43")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private LocalDateTime contactNextTime;

    @ApiModelProperty(value = "联系方式 (对应表字段 contact_type, 1:电话 2:微信 3:面谈 4:其他)", required = true, example = "1")
    private Integer contactType;

    @ApiModelProperty(value = "联系电话 (对应表字段 contact_phone)", example = "13800138000")
    private String contactPhone;

    @ApiModelProperty(value = "进展阶段 (对应表字段 stage, 1:潜在客户 2:意向客户 3:成交客户)", required = true, example = "1")
    private Integer stage;

    @ApiModelProperty(value = "创建者/跟进人ID (对应表字段 creator)", example = "1001")
    private Long creator;

    @ApiModelProperty(value = "跟进人姓名 (只读/展示用，非表字段)", example = "李老师")
    private String creatorName;

    @ApiModelProperty(value = "所属组织ID", example = "100")
    private Long orgId;

    @ApiModelProperty(value = "创建时间 (对应表字段 add_time)", example = "2026-03-18 12:51:43")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private LocalDateTime addTime;
}