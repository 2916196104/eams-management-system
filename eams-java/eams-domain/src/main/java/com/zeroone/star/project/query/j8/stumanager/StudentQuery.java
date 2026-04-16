package com.zeroone.star.project.query.j8.stumanager;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigInteger;

@Data
@ApiModel(value = "StudentQuery", description = "学员列表查询条件")
public class StudentQuery{

    @ApiModelProperty(value = "学员ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "学员姓名", example = "小明")
    private String name;

    @ApiModelProperty(value = "分校", example = "HN校区")
    private String branchSchool;

    @ApiModelProperty(value = "年级/阶段", example = "高三1班")
    private String grade;

    @ApiModelProperty(value = "授课老师姓名", example = "李老师")
    private String teacherName;

}