package com.zeroone.star.project.vo.j8.stumanager.SaveStu;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.Year;

@Data
@ApiModel("学员信息VO")
public class StuSaveVO {

    @ApiModelProperty(value = "学员ID")
    private Long id;

    @ApiModelProperty(value = "学员姓名")
    private String name;

    @ApiModelProperty(value = "性别 1男 2女")
    private Integer gender;

    @ApiModelProperty(value = "出生日期")
    private LocalDate birthday;

    @ApiModelProperty(value = "身份证号")
    private String idcard;

    @ApiModelProperty(value = "家长手机号")
    private String phone;

    @ApiModelProperty(value = "家长姓名")
    private String parentName;

    @ApiModelProperty(value = "亲属关系")
    private Integer familyRel;

    @ApiModelProperty(value = "所属校区ID")
    private Long schoolId;

    @ApiModelProperty(value = "入学日期")
    private LocalDate joinDate;

    @ApiModelProperty(value = "年级")
    private Year grade;

    @ApiModelProperty(value = "学员阶段")
    private Integer stage;

    @ApiModelProperty(value = "来源渠道")
    private Integer joinWay;

    @ApiModelProperty(value = "备注")
    private String remark;
}
