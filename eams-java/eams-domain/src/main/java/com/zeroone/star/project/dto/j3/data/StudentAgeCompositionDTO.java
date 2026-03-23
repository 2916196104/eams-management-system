package com.zeroone.star.project.dto.j3.data;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：在学学员年龄构成数据传输对象
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
@Data
public class StudentAgeCompositionDTO {
    @ApiModelProperty(value = "年龄", example = "7岁")
    private String age;

    @ApiModelProperty(value = "人数", example = "2140")
    private Integer count;

}
