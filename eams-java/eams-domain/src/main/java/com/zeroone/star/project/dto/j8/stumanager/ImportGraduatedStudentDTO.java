package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 导入结业学员DTO
 */
@Data
@ApiModel(value = "ImportGraduatedStudentDTO", description = "导入结业学员参数")
public class ImportGraduatedStudentDTO {

    @NotBlank(message = "姓名不能为空")
    @ApiModelProperty(value = "学员姓名", example = "张三", required = true)
    private String name;

    @NotBlank(message = "手机号不能为空")
    @ApiModelProperty(value = "家长手机号", example = "13800138000", required = true)
    private String mobile;

    @NotBlank(message = "登录密码不能为空")
    @ApiModelProperty(value = "登录密码", example = "123456", required = true)
    private String password;

    @NotNull(message = "分校ID不能为空")
    @ApiModelProperty(value = "分校ID", example = "1", required = true)
    private Long schoolId;

    @ApiModelProperty(value = "家长姓名", example = "李四")
    private String parentName;

    @ApiModelProperty(value = "亲属关系", example = "爸爸")
    private String familyRel;

    @ApiModelProperty(value = "性别", example = "男")
    private String gender;

    @ApiModelProperty(value = "身份证号", example = "110101200001011234")
    private String idCard;
}
