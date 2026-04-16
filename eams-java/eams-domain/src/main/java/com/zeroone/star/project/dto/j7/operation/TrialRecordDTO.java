package com.zeroone.star.project.dto.j7.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel("试听卡领取记录数据对象")
public class TrialRecordDTO {
    @ApiModelProperty(value = "记录ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "试听卡ID", example = "1")
    private Long trialId;

    @ApiModelProperty(value = "学生ID", example = "10001")
    private Long studentId;

    @ApiModelProperty(value = "课程ID", example = "1001")
    private Long courseId;

    @ApiModelProperty(value = "学生账号ID", example = "20001")
    private Long userId;

    @ApiModelProperty(value = "生成的学生课程关联ID", example = "30001")
    private Long studentCourseId;

    @ApiModelProperty(value = "领取时间", example = "2026-03-13 12:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "到期时间", example = "2026-04-13")
    private LocalDate expiredDate;

    @ApiModelProperty(value = "领取课时数量", example = "8")
    private Integer lessonCount;

    @ApiModelProperty(value = "学生所属学校ID", example = "5001")
    private Long schoolId;

    @ApiModelProperty(value = "学生顾问ID", example = "6001")
    private Long counselor;
}
