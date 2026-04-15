package com.zeroone.star.project.query.j2.sys.datadict;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class DictItemQuery extends PageQuery {
    /**
     * 数据名称
     */
    @ApiModelProperty("数据类型列表名称")
    private String name;
    /**
     * dict_id（外键）
     */
    @ApiModelProperty("字典类型ID")
    private Long dictId;
    /**
     * 描述/或信息
     */
    @ApiModelProperty("描述/信息")
    private  String info;
}
