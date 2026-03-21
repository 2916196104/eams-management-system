package com.zeroone.star.project.vo.j8.stumanager;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 跟进记录列表展示对象
 */
@Data
@ApiModel(value = "ContactRecordListVO", description = "跟进记录列表展示对象")
public class ContactRecordListVO {

    @ApiModelProperty(value = "记录ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "学员ID", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "跟进人ID", example = "1")
    private Long creator;

    @ApiModelProperty(value = "跟进人姓名", example = "管理员")
    private String creatorName;

    @ApiModelProperty(value = "联系时间", example = "2026-03-21 00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm", timezone = "GMT+8")
    private LocalDateTime contactTime;

    @ApiModelProperty(value = "下次联系时间", example = "2026-03-21 00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm", timezone = "GMT+8")
    private LocalDateTime contactNextTime;

    @ApiModelProperty(value = "联系方式", example = "电话")
    private String contactTypeName;

    @ApiModelProperty(value = "联系电话", example = "13800138000")
    private String contactPhone;

    @ApiModelProperty(value = "进展阶段", example = "目标客户阶段")
    private String stageName;

    @ApiModelProperty(value = "跟进记录内容", example = "客户有意向，需要跟进")
    private String info;

    @ApiModelProperty(value = "创建时间", example = "2026-03-21 13:47")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm", timezone = "GMT+8")
    private LocalDateTime addTime;
}
