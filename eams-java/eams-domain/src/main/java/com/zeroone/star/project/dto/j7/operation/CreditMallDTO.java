package com.zeroone.star.project.dto.j7.operation;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel("礼品对象")
public class CreditMallDTO {

    @ApiModelProperty("礼品ID")
    private Long id;

    @ApiModelProperty("礼品名称")
    private String name;

    @ApiModelProperty("封面图片")
    private String cover;

    @ApiModelProperty("所属学校ID")
    private Long schoolId;

    @ApiModelProperty("所属学校名称 (关联查询得出)")
    private String schoolName;

    @ApiModelProperty("兑换所需积分")
    private Integer credit;

    @ApiModelProperty("已兑换数量 ")
    private Integer exchangedCount;

    @ApiModelProperty("浏览次数 ")
    private Integer viewCount;

    @ApiModelProperty("最后编辑时间")
    private LocalDateTime lastUpdateTime;

    @ApiModelProperty("状态")
    private Integer status;

    @ApiModelProperty("物料ID")
    private String materialName;

    @ApiModelProperty("分类ID")
    private String categoryName;
}
