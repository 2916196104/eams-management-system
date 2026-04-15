package com.zeroone.star.project.DO;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import java.math.BigDecimal;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.hibernate.validator.constraints.Length;

/**
* 教师员工表
* @TableName staff
*/
@Data
public class Staff implements Serializable {
    /**
     *
     */
    @NotNull(message = "[]不能为空")
    @ApiModelProperty("")
    private Long id;
    /**
     * 姓名
     */
    @NotBlank(message = "[姓名]不能为空")
    @Size(max = 20, message = "编码长度不能超过20")
    @ApiModelProperty("姓名")
    @Length(max = 20, message = "编码长度不能超过20")
    private String name;
    /**
     * 手机号
     */
    @Size(max = 20, message = "编码长度不能超过20")
    @ApiModelProperty("手机号")
    @Length(max = 20, message = "编码长度不能超过20")
    private String mobile;
    /**
     * 微信登录id
     */
    @ApiModelProperty("微信登录id")
    private Long wxAccessId;
    /**
     * EMAIL
     */
    @Size(max = 100, message = "编码长度不能超过100")
    @ApiModelProperty("EMAIL")
    @Length(max = 100, message = "编码长度不能超过100")
    private String email;
    /**
     * 生日
     */
    @ApiModelProperty("生日")
    private Date birthday;
    /**
     * 性别
     */
    @ApiModelProperty("性别")
    private Integer gender;
    /**
     * 身份证
     */
    @Size(max = 20, message = "编码长度不能超过20")
    @ApiModelProperty("身份证")
    @Length(max = 20, message = "编码长度不能超过20")
    private String idCard;
    /**
     * 毕业学校
     */
    @Size(max = 50, message = "编码长度不能超过50")
    @ApiModelProperty("毕业学校")
    @Length(max = 50, message = "编码长度不能超过50")
    private String school;
    /**
     * 学历
     */
    @ApiModelProperty("学历")
    private Integer degree;
    /**
     * 备注
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("备注")
    @Length(max = 255, message = "编码长度不能超过255")
    private String remark;
    /**
     * 在职状态
     */
    @ApiModelProperty("在职状态")
    private Integer state;
    /**
     * 是否是管理者
     */
    @ApiModelProperty("是否是管理者")
    private Integer isManager;
    /**
     * 头像
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("头像")
    @Length(max = 255, message = "编码长度不能超过255")
    private String headImg;
    /**
     * 入职日期
     */
    @ApiModelProperty("入职日期")
    private Date hireDate;
    /**
     * 离职日期
     */
    @ApiModelProperty("离职日期")
    private Date fireDate;
    /**
     * 介绍
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("介绍")
    @Length(max = 255, message = "编码长度不能超过255")
    private String intro;
    /**
     * 创建时间
     */
    @ApiModelProperty("创建时间")
    private Date addTime;
    /**
     * 编辑时间
     */
    @ApiModelProperty("编辑时间")
    private Date editTime;
    /**
     * 创建人
     */
    @ApiModelProperty("创建人")
    private Long creator;
    /**
     * 编辑人
     */
    @ApiModelProperty("编辑人")
    private Long editor;
    /**
     * 是否删除
     */
    @ApiModelProperty("是否删除")
    private Integer deleted;
    /**
     * 密码
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("密码")
    @Length(max = 255, message = "编码长度不能超过255")
    private String password;
    /**
     * 课时费
     */
    @ApiModelProperty("课时费")
    private BigDecimal classFee;
    /**
     * 助教费
     */
    @ApiModelProperty("助教费")
    private BigDecimal assistantFee;
    /**
     * STAFF所属组织ID
     */
    @ApiModelProperty("STAFF所属组织ID")
    private Long orgId;
    /**
     * 是否内部人员
     */
    @ApiModelProperty("是否内部人员")
    private Integer isInner;

}