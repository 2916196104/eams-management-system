package com.zeroone.star.project.vo.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 作业提交列表
 */
@Data
@ApiModel("作业提交数据对象")
public class HomeworkSubmissionListVo {

    @ApiModelProperty(value="序号",example = "1")
    private Long id;

    @ApiModelProperty(value = "提交人",example = "张小明")
    private String name;

    @ApiModelProperty(value = "提交内容",example = "我干了Xxxxx")
    private String content;

    @ApiModelProperty(value = "提交时间",example = "2022.1.1")
    private LocalDateTime submit_time;

    @ApiModelProperty(value = "点评人",example = "1")
    private Long reviewer;

    @ApiModelProperty(value = "点评得分",example = "1")
    private Integer score;

    @ApiModelProperty(value = "点评内容",example = "xxxxx")
    private String comment_content;
}
