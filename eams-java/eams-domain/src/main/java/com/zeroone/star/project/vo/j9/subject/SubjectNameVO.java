package com.zeroone.star.project.vo.j9.subject;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(description = "科目名称视图对象")
public class SubjectNameVO {

    @ApiModelProperty(value = "科目唯一ID", example = "1", required = true)
    private Long id;

    @ApiModelProperty(value = "科目名称", example = "语文", required = true)
    private String subjectName;
}
