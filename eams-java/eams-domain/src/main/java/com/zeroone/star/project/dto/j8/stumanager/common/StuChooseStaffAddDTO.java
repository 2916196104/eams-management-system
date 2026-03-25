package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;


import javax.validation.constraints.NotBlank;

/**
 * <p>
 * 描述：经手人新增数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Data
@ApiModel("经手人新增数据传输对象")
public class StuChooseStaffAddDTO {
    @ApiModelProperty(value = "员工姓名", example = "张三")
    @NotBlank(message = "员工姓名不能为空")
    private String name;

    @ApiModelProperty(value = "职位名称", example = "课程顾问")
    @NotBlank(message = "职位名称不能为空")
    private String remark;
}
