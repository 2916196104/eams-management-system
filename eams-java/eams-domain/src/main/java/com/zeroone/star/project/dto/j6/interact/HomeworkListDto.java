package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.Date;

/**
 * 作业列表展示dto
 */
@Data
public class HomeworkListDto {

    @ApiModelProperty(value = "作业id",example = "1")
    private Long id;

    @ApiModelProperty(value = "标题",example = "数据结构")
    private String title;

    @ApiModelProperty(value = "班级",example = "1")
    private Long class_id;

    @ApiModelProperty(value = "发布者",example = "管理员")
    private String creator;

    @ApiModelProperty(value = "提交数",example = "0")
    private Integer submit_data;
    @ApiModelProperty(value = "发布时间",example = "2022.1.1")
    private LocalDateTime add_time;
}
