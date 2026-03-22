package com.zeroone.star.project.query.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：成绩单查询对象
 * </p>
 */
@Data

public class GradeFormQuery {
    @ApiModelProperty(value = "标题",example = "数据结构")
    private String title;

    @ApiModelProperty(value = "发布者id",example = "1")
    private Integer creator;
}
