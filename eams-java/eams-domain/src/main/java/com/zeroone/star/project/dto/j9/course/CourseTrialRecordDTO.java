package com.zeroone.star.project.dto.j9.course;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel("体验卡领取记录数据")
public class CourseTrialRecordDTO {

    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @NotNull(message = "体验卡ID不能为空")
    @ApiModelProperty(value = "体验卡ID", example = "1", required = true)
    private Long trialId;

    @NotNull(message = "学生ID不能为空")
    @ApiModelProperty(value = "学生ID", example = "201", required = true)
    private Long studentId;

    @ApiModelProperty(value = "课程ID", example = "101")
    private Long courseId;

    @ApiModelProperty(value = "学生账号ID", example = "301")
    private Long userId;

    @ApiModelProperty(value = "学生课程关联ID", example = "401")
    private Long studentCourseId;

    @ApiModelProperty(value = "领取时间", example = "2024-01-15 10:30:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "到期时间", example = "2024-01-22")
    private LocalDate expiredDate;

    @ApiModelProperty(value = "领取数量", example = "1")
    private Integer lessonCount;

    @ApiModelProperty(value = "学生所属学校ID", example = "1000")
    private Long schoolId;

    @ApiModelProperty(value = "学生的顾问", example = "1001")
    private Long counselor;
}
