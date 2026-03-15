package com.zeroone.star.project.query.j8;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel(description = "课程学员查询(含课次)")
public class StudentCourseQuery extends PageQuery {

    @ApiModelProperty(value = "课程ID")
    private Long courseId;

    @ApiModelProperty(value = "学员姓名")
    private String keyword;

}
