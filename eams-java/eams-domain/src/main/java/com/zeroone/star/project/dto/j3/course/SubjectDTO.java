package com.zeroone.star.project.dto.j3.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.validation.annotation.Validated;

import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：科目数据传输对象
 * </p>
 * @author fish
 * @version 1.0.0
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("科目数据传输对象")
@Validated
public class SubjectDTO {
    @ApiModelProperty(value = "科目Id", example = "3")
    @NotNull(message = "编号不能为空")
    private Long id;
    @ApiModelProperty(value = "科目名称", example = "信息")
    @NotNull(message = "科目名称不能为空")
    private String name;
    @ApiModelProperty(value = "简介", example = " ")
    private String info;
    @ApiModelProperty(value = "删除标记", example = "0")
    private Integer deleted;
    @ApiModelProperty(value = "排序值", example = "5")
    @NotNull(message = "排序值不能为空")
    private Integer sortNum;
}
