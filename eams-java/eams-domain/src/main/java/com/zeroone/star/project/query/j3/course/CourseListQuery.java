package com.zeroone.star.project.query.j3.course;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：课程列表查询参数
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("课程列表查询参数")
public class CourseListQuery extends PageQuery {
    @ApiModelProperty(value = "课程名称", example = "测试课程2")
    String name;
    @ApiModelProperty(value = "科目Id", example = "17")
    Long subjectId;
    @ApiModelProperty(value = "课程状态", example = "true")
    Boolean state;
    @ApiModelProperty(value = "适用年级Id", example = "4")
    Long gradeId;
}
