package com.zeroone.star.project.dto.j9.course;
import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalDateTime;

@Data
@ApiModel("课程章节数据")
public class CourseSectionDTO {
    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;


    @NotNull(message = "课程ID不能为空")
    @ApiModelProperty(value = "所属课程ID", example = "101", required = true)
    private Long courseId;

    @NotBlank(message = "章节标题不能为空")
    @ApiModelProperty(value = "章节标题", example = "第一章: Java基础", required = true)
    private String title;

    @NotNull(message = "计划课时数不能为空")
    @Min(value = 1, message = "计划课时数至少为1")
    @ApiModelProperty(value = "计划课时数", example = "10", required = true)
    private Integer lessonCount;

    @ApiModelProperty(value = "创建人ID", example = "1001")
    private Long creator;

    @ApiModelProperty(value = "编辑人ID", example = "1002")
    private Long editor;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "添加时间", example = "2024-01-15 10:30:00")
    private LocalDateTime addTime;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "编辑时间", example = "2024-01-20 14:30:00")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "删除标记: 0-未删除, 1-已删除", example = "0")
    private Integer deleted = 0;

}
