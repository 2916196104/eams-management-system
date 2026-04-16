package com.zeroone.star.project.query.j9.course;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

/**
 * 课程列表分页查询条件
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("课程列表查询条件")
public class CourseQuery extends PageQuery {

    @ApiModelProperty(value = "课程名（模糊搜索）", example = "Java")
    private String name;

    @ApiModelProperty(value = "学科ID", example = "10")
    private Long subjectId;

    @ApiModelProperty(value = "启用状态（0下架 1上架）", example = "1")
    private Integer state;

    @ApiModelProperty(value = "课堂类型（1大课 2小班课 3一对一）", example = "2")
    private Integer lessonType;

    @ApiModelProperty(value = "是否上架中（0否 1是）", example = "1")
    private Integer forSale;

    @ApiModelProperty(value = "适用学校/机构ID", example = "1")
    private Long orgId;

    @ApiModelProperty(value = "适用年级（模糊匹配）", example = "一年级")
    private String gradeName;
}
