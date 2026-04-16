package com.zeroone.star.project.query.j8.stumanager.common;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel(description = "学员课程数据查询(含课次)")
public class StudentCourseQuery extends PageQuery {

    @ApiModelProperty(value = "课程ID",example = "1")
    private Long courseId;

    @ApiModelProperty(value = "学员姓名",example = "张三")
    private String keyword;

}
