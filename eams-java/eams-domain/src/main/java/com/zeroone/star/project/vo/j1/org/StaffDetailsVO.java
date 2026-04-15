package com.zeroone.star.project.vo.j1.org;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
@Data
public class StaffDetailsVO {


    @ApiModelProperty(value = "姓名（必填）", example = "张三", required = true)
    private String name;

    @ApiModelProperty(value = "电话/登录账号（必填）", example = "13800138000", required = true)
    private String mobile;


    // ==================== 机构/职位 ====================
    @ApiModelProperty(value = "所属机构ID（必填）", example = "1", required = true)
    private Long orgId;

    @ApiModelProperty(value = "所属职位ID（必填）", example = "2", required = true)
    private Long positionId;

    // ==================== 个人信息 ====================
    @ApiModelProperty(value = "性别（0-未知 1-男 2-女）", example = "1")
    private Integer gender;

    @ApiModelProperty(value = "学历（对应 degree 字段）", example = "1")
    private Integer degree;

    @ApiModelProperty(value = "生日", example = "1990-01-01")
    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "GMT+8")
    private LocalDate birthday;

    @ApiModelProperty(value = "毕业学校", example = "XX大学")
    private String school;

    @ApiModelProperty(value = "入职日期", example = "2021-07-08")
    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "GMT+8")
    private LocalDate hireDate;


    // ==================== 业务费用 ====================
    @ApiModelProperty(value = "上课费/节（元）", example = "120.00")
    private BigDecimal classFee;

    @ApiModelProperty(value = "助教费/节（元）", example = "60.00")
    private BigDecimal assistantFee;

    // ==================== 系统标识 ====================
    @ApiModelProperty(value = "是否内部人员（0-否 1-是）", example = "1")
    private Integer isInner;

    @ApiModelProperty(value = "是否是管理者（0-否 1-是）", example = "0")
    private Integer isManager;

    // ==================== 其他信息 ====================
    @ApiModelProperty(value = "简介", example = "这是一位优秀的员工")
    private String remark;


}
