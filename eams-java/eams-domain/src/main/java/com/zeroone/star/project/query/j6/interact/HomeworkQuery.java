package com.zeroone.star.project.query.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 作业列表查询query
 */
@Data
public class HomeworkQuery {

    @ApiModelProperty(value = "标题",example = "数据结构")
    private String title;

    @ApiModelProperty(value = "班级",example = "1")
    private Long class_id;

    @ApiModelProperty(value = "创建人",example = "1")
    private Long creator;
}
