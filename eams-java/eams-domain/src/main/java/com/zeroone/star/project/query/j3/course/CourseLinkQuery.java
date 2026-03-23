package com.zeroone.star.project.query.j3.course;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：课程关联查询参数
 * </p>
 *  <p>版权：&copy;01星球</p>
 *  <p>地址：01星球总部</p>
 * @author j3组 KINGHOG
 * @version 1.0.0
 **/
@Data
public class CourseLinkQuery extends PageQuery {
    @ApiModelProperty(value = "课程id",example = "4")
    private Long courseId;
    @ApiModelProperty(value = "关联id",example = "2")
    private Long linkedId;
}
