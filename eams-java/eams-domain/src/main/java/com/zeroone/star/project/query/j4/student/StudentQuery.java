package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

//StudentQuery: 包含姓名、电话、状态（在线/意向/结业）、顾问ID、分页参数。
@Data
@ApiModel(description = "学员查询条件")
public class StudentQuery extends PageQuery {
    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String name;

    @ApiModelProperty(value = "手机号", example = "18864216425")
    private String mobile;

    @ApiModelProperty(value = "阶段", example = "在学学员")
    private String stage;

    @ApiModelProperty(value = "年级ID", example = "5")
    private Integer gradeId;

    @ApiModelProperty(value = "学员ID", example = "1", required = true)
    private String studentId;

    @ApiModelProperty("电话")
    private String phone;

    @ApiModelProperty(value = "状态")
    private String status;

    @ApiModelProperty(value = "顾问ID")
    private String advisorId;

    // 课程ID，用于筛选
    private Long courseId;
}