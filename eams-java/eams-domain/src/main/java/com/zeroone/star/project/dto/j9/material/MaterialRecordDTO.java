package com.zeroone.star.project.dto.j9.material;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel("物料记录数据")
public class MaterialRecordDTO {
        @ApiModelProperty(value = "物料记录ID")
        private Long id;
        @ApiModelProperty(value = "物料ID")
        private Long materialId;
        @ApiModelProperty(value = "变动数量")
        private Integer amount;
        @ApiModelProperty(value = "变动原因说明")
        private String reason;
        @ApiModelProperty(value = "变动类型（1入库/2出库/3调整）",example = "1")
        private Integer changeType;
        @ApiModelProperty(value = "变动对象id如积分商城里的商品id")
        private Long changeTargetId;
        @ApiModelProperty(value = "备注信息")
        private String remark;
        @ApiModelProperty(value = "变动时间")
        private LocalDateTime addTime;
        @ApiModelProperty(value = "涉及学生ID")
        private Long studentId;
        @ApiModelProperty(value = "涉及员工ID")
        private Long staffId;
}
