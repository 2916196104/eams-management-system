package com.zeroone.star.project.query.j3.supplies;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：物料出入库记录分页查询条件
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 */
@EqualsAndHashCode(callSuper = true)
@Data
@ApiModel("物料出入库记录查询对象")
public class MaterialRecordQuery extends PageQuery {

    @ApiModelProperty(value = "涉及学生ID", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "申请员工ID", example = "1")
    private Long applyStaffId;

    @ApiModelProperty(value = "变动类型 1入库 2出库 3积分商城出库", example = "1")
    private Integer changeType;

    @ApiModelProperty(value = "开始日期，格式：yyyy-MM-dd", example = "2026-01-01")
    private String beginDate;

    @ApiModelProperty(value = "结束日期，格式：yyyy-MM-dd", example = "2026-01-31")
    private String endDate;
}

