package com.zeroone.star.project.query.j2.sys.optlog;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description  操作日志-操作人选择列表查询对象
 * @title com.zeroone.star.project.query.j2.sys
 * @date 2026/3/22
 */
@Data
public class OptlogOperatorQuery extends PageQuery {
    @ApiModelProperty(value = "姓名", example = "管理员")
    private String name;
}

