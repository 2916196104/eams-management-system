package com.zeroone.star.project.vo.j7.interaction;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel(value = "作业详情VO")
public class HomeworkDetailVO {
    @ApiModelProperty(value = "作业ID")
    private Long id;

    @ApiModelProperty(value = "班级ID")
    private Long classId;

    @ApiModelProperty(value = "班级名称")
    private String className;

    @ApiModelProperty(value = "作业标题")
    private String title;

    @ApiModelProperty(value = "作业内容")
    private String content;

    @ApiModelProperty(value = "创建人ID")
    private Long creator;

    @ApiModelProperty(value = "创建人姓名")
    private String creatorName;

    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "最后编辑时间")
    private LocalDateTime editTime;
}