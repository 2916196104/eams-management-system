package com.zeroone.star.project.query.j2.sys.template;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 模板查询对象
 */
@Data
@ApiModel("模板查询对象")
public class TemplateQuery extends PageQuery {
    @ApiModelProperty(value = "模板名", example = "学员模板")
    private String fileName;
}
