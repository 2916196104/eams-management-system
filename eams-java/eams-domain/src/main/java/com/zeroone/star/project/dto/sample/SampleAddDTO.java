package com.zeroone.star.project.dto.sample;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import org.hibernate.validator.constraints.Range;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Pattern;

/**
 * <p>
 * 描述：添加数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Getter
@Setter
@ToString
@ApiModel("添加数据传输对象")
public class SampleAddDTO {
    @ApiModelProperty(value = "姓名", example = "张三")
    @NotBlank(message = "姓名不能为空")
    private String name;
    @ApiModelProperty(value = "性别", example = "男")
    @Pattern(regexp = "[男女]", message = "性别只能是男或女")
    private String sex;
    @ApiModelProperty(value = "年龄", example = "18")
    @Range(min = 0, max = 300, message = "年龄范围在0-300岁之间")
    private Integer age;
}
