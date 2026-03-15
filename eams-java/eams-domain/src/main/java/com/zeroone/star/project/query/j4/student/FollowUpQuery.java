package com.zeroone.star.project.query.j4.student;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：跟进记录查询对象
 */
@Data
public class FollowUpQuery extends PageQuery {

    @ApiModelProperty(value = "学员ID", example = "2008418408985583617")
    private Long studentId;

    @ApiModelProperty(value = "跟进人ID/姓名", example = "1001")
    private String followUserId;

    @ApiModelProperty(value = "跟进方式 (1:电话 2:微信 3:面谈 4:其他)", example = "1")
    private Integer followType;

    @ApiModelProperty(value = "开始时间", example = "2026-01-01 00:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime startTime;

    @ApiModelProperty(value = "结束时间", example = "2026-03-15 23:59:59")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime endTime;
}