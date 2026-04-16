package com.zeroone.star.project.dto.j6.interact;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDateTime;

/**
 * <p>
 * 广告/通知管理数据传输对象
 * </p>
 *
 * @author maban
 * @since 2026-03-17
 */
@Data
@ApiModel("广告信息数据传输对象")
public class AdvertisementDTO {

    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "标题", example = "欢迎使用系统")
    private String title;


    @ApiModelProperty(value = "类型（1-学生端首页Banner，2-学生端首页提示，3-学生端首页弹窗）", example = "1")
    private Integer type;

    @ApiModelProperty(value = "类型描述", example = "学生端首页Banner")
    private String typeDesc;

    @ApiModelProperty(value = "内容", example = "具体的广告内容文本")
    private String content;

    @ApiModelProperty(value = "封面图片地址", example = "http://example.com/img.jpg")
    private String cover;

    @ApiModelProperty(value = "创建者ID", example = "1")
    private Long creator;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "发布时间", example = "2026-03-17 10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "状态（0-禁用，1-启用）", example = "1")
    private Integer state;

    @ApiModelProperty(value = "排序值", example = "1")
    private Integer sortNum;

    @ApiModelProperty(value = "编辑者ID", example = "1")
    private Long editor;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "编辑时间", example = "2026-03-17 10:00:00")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "唯一码", example = "ADV_001")
    private String code;
}
