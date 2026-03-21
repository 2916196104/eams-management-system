package com.zeroone.star.project.query.j4.student;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：跟进记录查询对象 (对应 contact_record 表查询条件)
 */
@Data
public class FollowUpQuery extends PageQuery {

    @ApiModelProperty(value = "学员姓名或电话 (模糊查询)", example = "张三")
    private String keyword;

    @ApiModelProperty(value = "进展阶段 (对应表字段 stage)", example = "1")
    private Integer stage;

    @ApiModelProperty(value = "跟进人ID/姓名 (对应表字段 creator)", example = "1001")
    private String creator;

    @ApiModelProperty(value = "开始日期 (对应表字段 contact_time)", example = "2026-03-01 00:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime startTime;

    @ApiModelProperty(value = "结束日期 (对应表字段 contact_time)", example = "2026-03-31 23:59:59")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime endTime;

    // 如果需要按学生ID精确查询可保留，否则主要靠keyword
    @ApiModelProperty(value = "学生ID (精确查询)", example = "2008418408985583617")
    private Long studentId;
}