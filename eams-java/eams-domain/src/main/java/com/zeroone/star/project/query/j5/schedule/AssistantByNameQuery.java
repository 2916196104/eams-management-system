package com.zeroone.star.project.query.j5.schedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/*
* 描述：助教名称查询对象
* */
@Data
public class AssistantByNameQuery extends PageQuery {
    @ApiModelProperty(value = "助教名称",required = false,example = "张三")
    private String assistantName;
}
