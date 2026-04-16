package com.zeroone.star.project.query.j8.stumanager;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(value = "ClassHourSummaryQuery", description = "课时汇总列表查询条件")
public class ClassHourSummaryQuery extends PageQuery {

    @ApiModelProperty(value = "学员姓名", example = "小明")
    private String name;

    @ApiModelProperty(value = "课程", example = "S18的课程")
    private String courseId;
}