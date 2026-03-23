package com.zeroone.star.project.query.j5.classmanager;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;

public class ClassStudentQuery {

        @ApiModelProperty(value = "学员姓名（模糊匹配）", example = "张")
        private String studentName;

        @ApiModelProperty(value = "学号（模糊匹配）", example = "2023")
        private String studentNo;

        @ApiModelProperty(value = "性别 1男 2女", example = "1")
        private Integer gender;


    }
