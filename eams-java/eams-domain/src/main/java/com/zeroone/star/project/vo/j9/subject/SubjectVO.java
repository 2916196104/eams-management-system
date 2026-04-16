package com.zeroone.star.project.vo.j9.subject;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(description = "科目完整视图对象")
public class SubjectVO {

    @ApiModelProperty(value = "科目唯一ID",example = "1",required = true)
    private Long id;

    @ApiModelProperty(value = "科目名称",example = "语文",required = true)
    private String subjectName;

    @ApiModelProperty(value = "排序权重（从下往上递减）",example = "2",required = false)
    private Integer sortNum;

    @ApiModelProperty(value = "科目简介",example = "基础语文教学",required = false)
    private String info;
}
