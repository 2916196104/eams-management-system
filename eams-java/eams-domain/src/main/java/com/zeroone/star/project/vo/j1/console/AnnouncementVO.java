package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：公告视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("公告视图对象")
@Data
public class AnnouncementVO {

    @ApiModelProperty(value = "公告ID", example = "1001")
    private Long id;

    @ApiModelProperty(value = "标题", example = "关于2024年春季学期开学的通知")
    private String title;

    @ApiModelProperty(value = "添加时间", example = "2024-03-01 09:00:00")
    private String addTime;

    @ApiModelProperty(value = "修改时间", example = "2024-03-05 14:00:00")
    private String editTime;
}
