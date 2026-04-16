package com.zeroone.star.project.dto.j8.stumanager.OnlineStu;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：在线学员导入数据
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 麦
 * @version 1.0.0
 */
@ApiModel("导入导出学员数据对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class ImportAndExportStudentDTO {
    @ApiModelProperty(value = "用户名", example = "admin", required = true)
    private String name;

    @ApiModelProperty(value = "手机号", example = "12345678901", required = true)
    private String phoneNumber;

    @ApiModelProperty(value = "密码", example = "123456", required = true)
    private String password;

    @ApiModelProperty(value = "家长姓名", example = "张三")
    private String parentName;

    @ApiModelProperty(value = "性别", example = "男")
    private String gender;

    @ApiModelProperty(value = "出生日期", example = "2000-01-01")
    private String birthDate;

    @ApiModelProperty(value = "身份证号", example = "11010519900307002X")
    private String idCardNumber;
}
