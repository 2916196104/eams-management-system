package com.zeroone.star.project.query.j7.interaction;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：作业列表查询对象
 * </p>
 * @author lvincent
 * @since 2026-03-15
 */
@EqualsAndHashCode(callSuper = true)
@Data
@ApiModel("作业列表查询对象")
public class HomeworkListQuery extends PageQuery {

    @ApiModelProperty(value = "标题关键词（模糊搜索）", example = "课后")
    private String title;

    @ApiModelProperty(value = "班级ID", example = "1")
    private Long classId;

    @ApiModelProperty(value = "教师ID", example = "1")
    private Long teacherId;
}
