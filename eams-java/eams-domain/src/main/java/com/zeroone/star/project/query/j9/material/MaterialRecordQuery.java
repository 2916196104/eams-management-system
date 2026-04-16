package com.zeroone.star.project.query.j9.material;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

/**
 * 描述：物料记录查询条件
 */
@Getter
@Setter
@ToString
@ApiModel("物料记录查询条件")
public class MaterialRecordQuery extends PageQuery {
    @ApiModelProperty(value = "物料ID")
    private Long materialId;
    @ApiModelProperty(value = "变动类型（1入库/2出库/3调整）",example = "1")
    private Integer changeType;
    @ApiModelProperty(value = "涉及学生ID")
    private Long studentId;
    @ApiModelProperty(value = "涉及员工ID")
    private Long staffId;
}

