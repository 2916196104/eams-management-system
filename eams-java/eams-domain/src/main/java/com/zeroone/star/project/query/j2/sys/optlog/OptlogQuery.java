package com.zeroone.star.project.query.j2.sys.optlog;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description  操作日志查询对象
 * @title com.zeroone.star.project.query.j2.sys
 * @date 2026/3/15
 */
@Data
public class OptlogQuery extends PageQuery {
    @ApiModelProperty(value = "操作类型",example = "老师登录")
    private String type;

    @ApiModelProperty(value = "操作内容",example = "登录成功")
    private String info;

    @ApiModelProperty(value = "操作人的id",example = "1")
    private Integer operator;
}
