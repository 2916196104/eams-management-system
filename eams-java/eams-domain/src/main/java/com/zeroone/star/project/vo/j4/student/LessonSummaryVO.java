package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDateTime;

@Data
@ApiModel(description = "学员课时汇总VO")
public class LessonSummaryVO {
    @ApiModelProperty(value = "关联记录ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "课时ID", example = "1001")
    private Long lessonId;

    @ApiModelProperty(value = "班级ID", example = "2001")
    private Integer classId;

    @ApiModelProperty(value = "学员ID", example = "1")
    private String studentId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String name;

    @ApiModelProperty(value = "手机号", example = "18864216425")
    private String mobile;

    @ApiModelProperty(value = "扣减课时数", example = "1")
    private Integer decLessonCount;

    @ApiModelProperty(value = "总课时数", example = "10")
    private Integer lessonCount;

    @ApiModelProperty(value = "教师ID", example = "3001")
    private Long teacherId;

    @ApiModelProperty(value = "签到时间", example = "2025-03-18 14:30:00")
    private LocalDateTime signTime;

    @ApiModelProperty(value = "签到类型", example = "1")
    private Integer signType;

    @ApiModelProperty(value = "签到状态", example = "1")
    private Integer signState;
}