package com.zeroone.star.project.query.j6.interact;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 广告/通知管理列表查询条件
 */
@Data
@ApiModel("广告列表查询条件")
public class AdvertisementListQuery extends PageQuery {

    @ApiModelProperty(value = "标题", example = "欢迎")
    private String title;

    @ApiModelProperty(value = "类型（1-学生端首页Banner，2-学生端首页提示，3-学生端首页弹窗）", example = "1")
    private Integer type;

    @ApiModelProperty(value = "状态（0-禁用，1-启用）", example = "1")
    private Integer state;
}
