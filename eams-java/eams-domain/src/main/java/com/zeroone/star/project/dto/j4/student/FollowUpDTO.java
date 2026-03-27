package com.zeroone.star.project.dto.j4.student;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：跟进记录传输对象 (DTO) - 仅用于新增
 * 设计原则：严格匹配前端原型图字段，不包含主键ID
 * 系统字段（如创建人、组织ID、学生姓名等）由后端自动填充。
 */
@Data
public class FollowUpDTO {

    @ApiModelProperty(value = "学生ID", required = true, example = "20084184087")
    @NotNull(message = "学生ID不能为空")
    private Long studentId;

    // ================= 原型图必填项 (*号) =================

    @ApiModelProperty(value = "跟进阶段", required = true, example = "1", notes = "1:潜在客户 2:意向客户 3:成交客户")
    @NotNull(message = "跟进阶段不能为空")
    private Integer progressStage;

    @ApiModelProperty(value = "联系途径", required = true, example = "1", notes = "1:电话 2:微信 3:面谈 4:其他")
    @NotNull(message = "联系途径不能为空")
    private Integer contactChannel;

    @ApiModelProperty(value = "联系时间", required = true, example = "2026-03-15 16:20:00")
    @NotNull(message = "联系时间不能为空")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private LocalDateTime contactTime;

    @ApiModelProperty(value = "跟进记录内容", required = true, example = "与客户沟通了课程细节，客户意向强烈")
    @NotBlank(message = "跟进记录内容不能为空")
    private String followUpContent;

    // ================= 原型图选填项 =================

    @ApiModelProperty(value = "下次联系时间", example = "2026-03-20 10:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private LocalDateTime nextContactTime;

    @ApiModelProperty(value = "联系方式详情,电话号或微信号", example = "13800138000")
    private String contactDetail;
    @ApiModelProperty(value = "跟进人ID (系统自动填充)", hidden = true)
    private Long creatorId;


    @ApiModelProperty(value = "所属组织ID (系统自动填充)", hidden = true)
    private Long orgId;
}