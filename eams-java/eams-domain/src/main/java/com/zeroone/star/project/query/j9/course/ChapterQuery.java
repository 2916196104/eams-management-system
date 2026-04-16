package com.zeroone.star.project.query.j9.course;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：章节查询对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel("章节查询对象")
public class ChapterQuery extends PageQuery {
    @ApiModelProperty(value = "课程ID", example = "1")
    private Long courseId;

    @ApiModelProperty(value = "章节名称", example = "第一章")
    private String chapterName;
}