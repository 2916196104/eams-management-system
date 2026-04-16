package com.zeroone.star.project.query.j6.eas;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 年级列表查询对象
 */
@Data
public class GradeManagerQuery extends PageQuery {
    @ApiModelProperty(value = "年级名称")
    private String name;

    @ApiModelProperty(value = "入学年份")
    private Integer year;

}
