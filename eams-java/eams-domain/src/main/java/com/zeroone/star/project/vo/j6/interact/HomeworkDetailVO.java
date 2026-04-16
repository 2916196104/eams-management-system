package com.zeroone.star.project.vo.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
public class HomeworkDetailVO {


    @ApiModelProperty(value="作业id",example = "1")
    private Long id;

    @ApiModelProperty(value = "班级",example = "1")
    private Long class_id;

    @ApiModelProperty(value = "标题",example = "测试作业标题")
    private String title;

    @ApiModelProperty(value = "提交内容",example = "我干了Xxxxx")
    private String content;


}
