package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：报名签单数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Data
@ApiModel("报名签单数据传输对象")
public class StuSignCourseDTO extends StuSignCourseAddDTO {
    @ApiModelProperty(value = "报名签单主键ID", example = "123456")
    @NotNull(message = "报名签单主键ID不能为空")
    private Long id;
}