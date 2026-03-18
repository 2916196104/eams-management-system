package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

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


    @ApiModelProperty(value = "图片", example = "广告图片URL", required = true)
    private String imageUrl;

    @ApiModelProperty(value = "类型", example = "学生端首页Banner", required = true)
    private List<String> type;

    @ApiModelProperty(value = "标题", example = "欢迎使用系统", required = true )
    private String title;

    @ApiModelProperty(value = "内容", example = "具体的广告内容文本", required = true)
    private String content;


    @ApiModelProperty(value = "发布者", example = "admin")
    private String creator;

    @ApiModelProperty(value = "发布时间", example = "2026-03-17 10:00:00")
    private LocalDateTime createTime;

    @ApiModelProperty(value = "操作", example = "editor")
    private Long editor;

    @ApiModelProperty(value = "状态", example = "1")
    private Integer state;

}