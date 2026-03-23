package com.zeroone.star.project.query.j5.courseschedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class StudentStatusQuery extends PageQuery {
    @ApiModelProperty( value = "课程编号", example = "1")
    private String courseId;

}
