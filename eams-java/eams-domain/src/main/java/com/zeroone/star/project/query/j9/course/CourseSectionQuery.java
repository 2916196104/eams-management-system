package com.zeroone.star.project.query.j9.course;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

/**
 * 章节列表分页查询条件
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("章节列表查询条件")
public class CourseSectionQuery extends PageQuery {

    @ApiModelProperty(value = "课程ID", required = true, example = "100")
    private Long courseId;

    @ApiModelProperty(value = "章节标题（模糊搜索）", example = "Java")
    private String title;
}
