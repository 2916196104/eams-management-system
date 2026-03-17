package com.zeroone.star.project.query;


import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：课程章节分页查询参数
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author j3组 殇昌
 * @version 1.0.0
 */
@Data
public class CourseSectionPageQuery extends PageQuery {

    @ApiModelProperty(value = "所属课程id", example = "1001", required = true)
    private Long courseId;

    @ApiModelProperty(value = "章节标题", example = "素描")
    private String title;
}