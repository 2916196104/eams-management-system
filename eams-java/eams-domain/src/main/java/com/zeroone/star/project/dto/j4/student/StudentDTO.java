package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDate;

@Data
@ApiModel(description = "学员数据传输对象")
public class StudentDTO {
    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String name;

    @ApiModelProperty(value = "手机号", example = "18864216425")
    private String mobile;

    @ApiModelProperty(value = "家长姓名", example = "李四")
    private String parentName;

    @ApiModelProperty(value = "亲属关系", example = "爸爸")
    private String familyRel;

    @ApiModelProperty(value = "性别", example = "男")
    private String gender;

    @ApiModelProperty(value = "生日", example = "2026-03-11")
    private LocalDate birthday;

    @ApiModelProperty(value = "身份证号", example = "411723822525798457")
    private String idcard;

    @ApiModelProperty(value = "报名方式", example = "4")
    private Integer joinWay;

    @ApiModelProperty(value = "报名日期", example = "2026-03-02")
    private LocalDate joinDate;

    @ApiModelProperty(value = "年级ID", example = "5")
    private Integer gradeId;

    @ApiModelProperty(value = "备注", example = "wu")
    private String remark;

    @ApiModelProperty(value = "阶段", example = "在学学员")
    private String stage;
}