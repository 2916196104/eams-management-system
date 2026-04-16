package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：课程选择数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Data
@ApiModel("课程选择数据传输对象")
public class StuChooseCourseDTO extends StuChooseCourseAddDTO {

    @ApiModelProperty(value = "课程主键ID", example = "1d7b0520e93e72715d5d6af1fb7d9a37")
    @NotNull(message = "课程主键ID不能为空")
    private Long id;

    @ApiModelProperty(value = "经手人ID", example = "1")
    @NotNull(message = "经手人ID不能为空")
    private Long operator;
}