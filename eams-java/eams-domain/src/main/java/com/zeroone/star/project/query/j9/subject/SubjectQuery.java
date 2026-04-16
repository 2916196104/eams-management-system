package com.zeroone.star.project.query.j9.subject;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@ApiModel(description = "科目分页查询条件")
@EqualsAndHashCode(callSuper = true)
public class SubjectQuery extends PageQuery {

    @ApiModelProperty(value = "科目名称（支持模糊查询）",example = "语文",required = false)
    private String subjectName;
}
