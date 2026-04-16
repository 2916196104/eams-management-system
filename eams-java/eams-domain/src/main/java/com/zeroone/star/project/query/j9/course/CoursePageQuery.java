package com.zeroone.star.project.query.j9.course;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("课程分页查询条件")
public class CoursePageQuery extends PageQuery {
    @ApiModelProperty(value = "课程名称",example = "实例课程")
    private String name;
    @ApiModelProperty(value = "科目Id",example = "1")
    private Long subjectId;
    @ApiModelProperty(value = "课程状态",example = "1")
    private Integer state;
    @ApiModelProperty(value = "适用年级名",example = "2024级")
    private String gradeNames;
}
