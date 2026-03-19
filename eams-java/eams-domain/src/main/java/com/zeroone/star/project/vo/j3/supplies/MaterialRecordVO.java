package com.zeroone.star.project.vo.j3.supplies;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：物料出入库记录列表显示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 */
@Data
@ApiModel("物料出入库记录显示对象")
public class MaterialRecordVO {

    @ApiModelProperty(value = "记录ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "物料名称", example = "笔记本")
    private String materialName;

    @ApiModelProperty(value = "变动数量，入库为正，出库为负", example = "100")
    private Integer amount;

    @ApiModelProperty(value = "申请员工名称", example = "张老师")
    private String applyStaffName;

    @ApiModelProperty(value = "涉及学生名称", example = "张小明")
    private String studentName;

    @ApiModelProperty(value = "变动类型 1入库 2出库 3积分商城出库", example = "1")
    private Integer changeType;

    @ApiModelProperty(value = "变动类型名称", example = "入库")
    private String changeTypeName;

    @ApiModelProperty(value = "变动时间，格式：yyyy-MM-dd HH:mm:ss", example = "2026-03-16 10:00:00")
    private String changeTime;
}

