package com.zeroone.star.project.DO.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel(description = "教师DO")
public class StaffDo {
    @ApiModelProperty(value = "ID")
    private Long id;
    @ApiModelProperty(value = "姓名")
    private String name;
    @ApiModelProperty(value = "手机号")
    private String mobile;
    @ApiModelProperty(value = "微信ID")
    private Long wxAccessId;
    @ApiModelProperty(value = "邮箱")
    private String email;
    @ApiModelProperty(value = "生日")
    private LocalDate birthday;
    @ApiModelProperty(value = "性别")
    private Integer gender;
    @ApiModelProperty(value = "身份证号")
    private String idCard;
    @ApiModelProperty(value = "毕业院校")
    private String school;
    @ApiModelProperty(value = "学历")
    private Integer degree;
    @ApiModelProperty(value = "备注")
    private String remark;
    @ApiModelProperty(value = "状态")
    private Integer state;
    @ApiModelProperty(value = "是否管理员")
    private Integer isManager;
    @ApiModelProperty(value = "头像")
    private String headImg;
    @ApiModelProperty(value = "入职日期")
    private LocalDate hireDate;
    @ApiModelProperty(value = "离职日期")
    private LocalDate fireDate;
    @ApiModelProperty(value = "简介")
    private String intro;
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;
    @ApiModelProperty(value = "编辑时间")
    private LocalDateTime editTime;
    @ApiModelProperty(value = "创建人")
    private Long creator;
    @ApiModelProperty(value = "编辑人")
    private Long editor;
    @ApiModelProperty(value = "删除标记")
    private Integer deleted;
    @ApiModelProperty(value = "密码")
    private String password;
    @ApiModelProperty(value = "授课费")
    private BigDecimal classFee;
    @ApiModelProperty(value = "助教费")
    private BigDecimal assistantFee;
    @ApiModelProperty(value = "机构ID")
    private Long orgId;
    @ApiModelProperty(value = "是否内部员工")
    private Integer isInner;
}
