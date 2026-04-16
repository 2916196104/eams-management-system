package com.zeroone.star.project.query.j6.interact;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 作业列表查询query
 */
@Data
public class HomeworkQuery extends PageQuery {

    @ApiModelProperty(value = "标题",example = "数据结构")
    private String title;

    @ApiModelProperty(value = "班级",example = "1")
    private Long class_id;

    @ApiModelProperty(value = "发布者",example = "管理员")
    private String creator;
}
