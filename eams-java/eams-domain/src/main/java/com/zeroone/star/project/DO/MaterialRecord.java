package com.zeroone.star.project.DO;

import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.Date;

@Data
@TableName("material_record")
public class MaterialRecord implements Serializable {
    @ApiModelProperty("主键")
    private Long id;
    @ApiModelProperty("物料ID")
    private Long materialId;
    @ApiModelProperty("变动数量")
    private Integer amount;
    @ApiModelProperty("变动原因说明")
    private String reason;
    @ApiModelProperty("变动类型1入库2出库3积分商城出库")
    private Integer changeType;
    @ApiModelProperty("变动对象id如积分商城里的商品id")
    private Long changeTargetId;
    @ApiModelProperty("备注信息")
    private String remark;
    @ApiModelProperty("创建人")
    private Long creator;
    @ApiModelProperty("编辑人")
    private Long editor;
    @ApiModelProperty("变动时间")
    private Date addTime;
    @ApiModelProperty("编辑时间")
    private Date editTime;
    @ApiModelProperty("删除标记")
    private Integer deleted;
    @ApiModelProperty("涉及学生id")
    private Long studentId;
    @ApiModelProperty("涉及员工id")
    private Long staffId;
    @ApiModelProperty("所属物料的组织ID")
    private Long orgId;
    @ApiModelProperty("学校id")
    private Long schoolId;
}
