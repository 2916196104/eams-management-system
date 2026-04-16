package com.zeroone.star.project.query.j9.operation;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;
import org.springframework.format.annotation.DateTimeFormat;

import java.util.Date;

/**
 * 课程体验卡领取记录分页查询参数
 */
@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel(description = "课程体验卡领取记录分页查询参数")
public class CourseTrialRecordPageQuery extends PageQuery {

    @ApiModelProperty(value = "卡ID", example = "1001")
    private Long trialId;

    @ApiModelProperty(value = "学生ID", example = "20260317001")
    private Long studentId;

    @ApiModelProperty(value = "课程ID", example = "3001")
    private Long courseId;

    @ApiModelProperty(value = "学校ID", example = "10001")
    private Long schoolId;

    @ApiModelProperty(value = "领取时间-开始", example = "2026-01-01 00:00:00")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date addTimeStart;

    @ApiModelProperty(value = "领取时间-结束", example = "2026-03-31 23:59:59")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date addTimeEnd;

    @ApiModelProperty(value = "到期时间-开始", example = "2026-04-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private Date expiredDateStart;

    @ApiModelProperty(value = "到期时间-结束", example = "2026-06-30")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private Date expiredDateEnd;

    @ApiModelProperty(value = "学生顾问ID", example = "4001")
    private Long counselor;
}
