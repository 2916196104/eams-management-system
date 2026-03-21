package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

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

    @ApiModelProperty(value = "学员ID", example = "1")
    private String studentId;

    @ApiModelProperty("姓名")
    private String name;

    @ApiModelProperty("电话")
    private String phone;

    @ApiModelProperty("状态")
    private String status;

    @ApiModelProperty("顾问ID")
    private String advisorId;
}