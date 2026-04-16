package com.zeroone.star.project.query.j6.interact;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：成绩单查询对象
 * </p>
 */
@Data

public class GradeFormQuery extends PageQuery {
    @ApiModelProperty(value = "标题",example = "数据结构")
    private String title;

    @ApiModelProperty(value = "发布者id",example = "1")
    private Long creator;
}
