package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 公告数据传输对象
 * </p>
 *
 * @author maban
 * @since 2026-03-17
 */
@Data
@ApiModel("公告信息数据传输对象")
public class AdvertisementDTO {

    @ApiModelProperty(value = "标题id", example = "1")
    private Long id;

    @ApiModelProperty(value = "类型", example = "学生端首页Banner", required = true)
    private String type;

    @ApiModelProperty(value = "学生端首页提示", example = "欢迎使用系统", required = true )
    private String title;

    @ApiModelProperty(value = "内容", example = "具体的广告内容文本", required = true)
    private String content;

    @ApiModelProperty(value = "链接", example = "https://example.com")
    private String url;

    @ApiModelProperty(value = "创建者", example = "admin")
    private String creator;

    @ApiModelProperty(value = "创建时间", example = "2026-03-17 10:00:00")
    private LocalDateTime createTime;

    @ApiModelProperty(value = "逻辑删除", example = "0")
    private Integer deleted;

    @ApiModelProperty(value = "编辑时间", example = "2026-03-17 15:30:00")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "编辑者", example = "editor")
    private Long editor;

    @ApiModelProperty(value = "状态", example = "1")
    private Integer state;

    @ApiModelProperty(value = "排序", example = "1")
    private Integer sort;
}