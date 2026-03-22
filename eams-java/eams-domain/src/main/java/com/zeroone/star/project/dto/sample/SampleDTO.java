package com.zeroone.star.project.dto.sample;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;

/**
 * <p>
 * 描述：示例数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Data
@ApiModel("示例传输数据对象")
public class SampleDTO extends SampleAddDTO {
    @ApiModelProperty(value = "编号", example = "1d7b0520e93e72715d5d6af1fb7d9a37")
    @NotBlank(message = "编号不能为空")
    private String id;
}
