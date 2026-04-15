package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalTime;
import java.util.List;

@Data
@ApiModel("批量修改课次 DTO")
public class BatchUpdateCourseDTO {

    @ApiModelProperty(value = "课程ID列表", required = true, example = "1,2,3")
    private List<Long> updateIds;

    @ApiModelProperty(value = "增减天数", example = "1")
    private Integer changeDays;

    @ApiModelProperty(value = "开始时间", example = "00:00:00")
    @DateTimeFormat(pattern = "HH:mm")
    private LocalTime startTime;

    @ApiModelProperty(value = "结束时间", example = "23:59:59")
    @DateTimeFormat(pattern = "HH:mm")
    private LocalTime endTime;

    @ApiModelProperty(value = "教室ID", example = "1")
    private Long roomId;

    @ApiModelProperty(value = "主讲老师id集合",example = "1,2")
    private List<Long> teacherIds;

    @ApiModelProperty(value = "助教老师id集合",example = "1,2")
    private List<Long> assistantIds;
}
