package com.zeroone.star.project.dto.j9.subject;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;

@Data
@ApiModel(description = "科目数据传输对象")
public class SubjectDTO {

    @ApiModelProperty(value = "科目ID（新增不传，更新必须填）",example = "1",required = false)
    private Long id;

    @NotBlank(message = "科目名称不能为空")
    @ApiModelProperty(value = "科目名称",example = "语文",required = true)
    private String name;

    @ApiModelProperty(value = "排序权重（从下往上递减）",example = "2",required = false)
    private Integer sortNum;

    @ApiModelProperty(value = "科目简洁",example = "基础语文教学",required = false)
    private String info;
}
