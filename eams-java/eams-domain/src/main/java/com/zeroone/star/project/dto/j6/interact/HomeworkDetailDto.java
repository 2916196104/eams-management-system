package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 作业详情Dto
 */
@Data
@ApiModel("作业详情")
public class HomeworkDetailDto {

    @ApiModelProperty(value = "作业id",example = "1")
    private Long id;

    @ApiModelProperty(value = "班级",example = "1")
    private Long class_id;

    @ApiModelProperty(value = "标题",example = "数据结构")
    private String title;

    @ApiModelProperty(value = "作业内容",example = "完成xxxx习题")
    private String content;
}
