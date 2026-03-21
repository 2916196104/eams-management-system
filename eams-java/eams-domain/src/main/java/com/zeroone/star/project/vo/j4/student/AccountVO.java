package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 账号信息VO
 */
@Data
@ApiModel(description = "账号信息VO")
public class AccountVO {
    @ApiModelProperty(value = "账号ID", example = "10001")
    private Long accountId;

    @ApiModelProperty(value = "账号名称", example = "admin")
    private String accountName;

    @ApiModelProperty(value = "真实姓名", example = "管理员")
    private String realName;

    @ApiModelProperty(value = "手机号", example = "13800138001")
    private String phone;

    @ApiModelProperty(value = "账号状态（1启用/0禁用）", example = "1")
    private Integer status;

    @ApiModelProperty(value = "所属部门ID", example = "1001")
    private Long deptId;

    @ApiModelProperty(value = "所属部门名称", example = "技术部")
    private String deptName;

    @ApiModelProperty(value = "创建时间", example = "2024-06-30 15:30:00")
    private LocalDateTime createTime;

    @ApiModelProperty(value = "最后登录时间", example = "2024-06-30 16:00:00")
    private LocalDateTime lastLoginTime;
}