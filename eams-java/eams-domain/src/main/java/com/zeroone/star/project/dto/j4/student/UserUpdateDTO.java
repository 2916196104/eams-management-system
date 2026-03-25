package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

@Data
@ApiModel("修改账号信息")
public class UserUpdateDTO {

    @NotNull(message = "账号ID不能为空")
    @ApiModelProperty(value = "账号ID", required = true)
    private Long id;

    @NotBlank(message = "姓名不能为空")
    @ApiModelProperty(value = "家长姓名", required = true)
    private String name;

    @NotBlank(message = "手机号不能为空")
    @ApiModelProperty(value = "手机号", required = true)
    private String mobile;

    @ApiModelProperty("邮箱")
    private String email;

    @ApiModelProperty("账号状态 0禁用 1正常")
    private Integer state;

    @ApiModelProperty("所属学校ID")
    private Long schoolId;

    @ApiModelProperty("备注")
    private String remark;
}