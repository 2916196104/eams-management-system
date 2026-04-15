package com.zeroone.star.project.dto.j5.courseschedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel(value = "课次查询DTO", description = "课次分页查询参数")
public class LessonQueryDTO extends PageQuery {

    @ApiModelProperty(value = "是否试听")
    private Integer onTrial;

    @ApiModelProperty(value = "课程ID")
    private Long courseId;

    @ApiModelProperty(value = "班级ID")
    private Long classId;

    @ApiModelProperty(value = "教师ID")
    private Long teacherId;

    @ApiModelProperty(value = "教室ID")
    private Long roomId;

    @ApiModelProperty(value = "开始日期")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;

    @ApiModelProperty(value = "课次状态")
    private Integer state;
}
