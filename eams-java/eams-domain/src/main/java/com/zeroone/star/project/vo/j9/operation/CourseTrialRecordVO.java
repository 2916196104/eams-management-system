package com.zeroone.star.project.vo.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.Date;

/**
 * 课程体验卡领取记录VO
 */
@Data
@ApiModel(description = "课程体验卡领取记录VO")
public class CourseTrialRecordVO {

    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "卡ID", example = "1001")
    private Long trialId;

    @ApiModelProperty(value = "学生ID", example = "20260317001")
    private Long studentId;

    @ApiModelProperty(value = "课程ID", example = "3001")
    private Long courseId;

    @ApiModelProperty(value = "学生账号ID", example = "5001")
    private Long userId;

    @ApiModelProperty(value = "学生课程关联ID", example = "6001")
    private Long studentCourseId;

    @ApiModelProperty(value = "领取时间", example = "2026-03-17 10:00:00")
    private Date addTime;

    @ApiModelProperty(value = "到期时间", example = "2026-04-17")
    private Date expiredDate;

    @ApiModelProperty(value = "剩余可预约课时数", example = "3")
    private Integer lessonCount;

    @ApiModelProperty(value = "学生所属学校ID", example = "10001")
    private Long schoolId;

    @ApiModelProperty(value = "学生顾问ID", example = "4001")
    private Long counselor;
}
