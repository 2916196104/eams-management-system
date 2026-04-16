package com.zeroone.star.project.dto.j6.interact;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

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
public class AnnouncementDTO {

    @ApiModelProperty(value = "公告ID", example = "1768472940128731136")
    private Long id;

    @ApiModelProperty(value = "图片URL", example = "http://xxx/group1/xxx.jpg")
    private String imageUrl;

    @ApiModelProperty(value = "类型(1-学生端首页弹出,2-学生端首页公告,3-学生端首页Banner,4-普通公告)", example = "3")
    private Integer type;

    @ApiModelProperty(value = "类型名称", example = "学生端首页Banner")
    private String typeName;

    @ApiModelProperty(value = "标题", example = "欢迎使用系统", required = true)
    private String title;

    @ApiModelProperty(value = "内容", example = "具体的公告内容文本", required = true)
    private String content;

    @ApiModelProperty(value = "发布者ID", example = "1768472939012456448")
    private Long creatorId;

    @ApiModelProperty(value = "发布者姓名", example = "管理员")
    private String creatorName;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "发布时间", example = "2026-03-17 10:00:00")
    private LocalDateTime createTime;

    @ApiModelProperty(value = "状态(0-停用,1-启用)", example = "1")
    private Integer state;

}