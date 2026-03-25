package com.zeroone.star.project.vo.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel(value = "StudentVO", description = "学员信息展示对象")
public class StudentVO {

    @ApiModelProperty(value = "阶段/年级", example = "高中三年级")
    private String stage;

    @ApiModelProperty(value = "性别 0-女 1-男", example = "1")
    private Integer gender;

    @ApiModelProperty(value = "年龄", example = "18")
    private Integer age;

    @ApiModelProperty(value = "出生日期", example = "2005-10-01")
    private LocalDate birthday;

    @ApiModelProperty(value = "身份证号码", example = "430123200510011234")
    private String idcard;

    @ApiModelProperty(value = "家长姓名", example = "小李")
    private String name;

    @ApiModelProperty(value = "家庭关系", example = "父亲")
    private FamilyRelEnum familyRel;

    @ApiModelProperty(value = "年级", example = "8")
    private String grade_id;

    @ApiModelProperty(value = "入学日期", example = "2022-09-01")
    private LocalDate joinDate;

    @ApiModelProperty(value = "加入时间", example = "2026-03-24")
    private LocalDate addtime;

}