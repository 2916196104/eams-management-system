package com.zeroone.star.project.vo.j8.sysmanager;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.io.Serializable;
import java.util.Date;

@Data
@ApiModel(value = "NoticeVO", description = "公告视图对象")
public class NoticeVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "标题", example = "hellow")
    private String title;

    @ApiModelProperty(value = "内容（HTML格式）", example = "<p>hi</p>")
    private String content;

    @ApiModelProperty(value = "浏览量", example = "0")
    private Integer viewNum;

    @ApiModelProperty(value = "创建者ID", example = "1")
    private Long creator;

    @ApiModelProperty(value = "创建者名称", example = "管理员")
    private String creatorName;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @ApiModelProperty(value = "创建时间", example = "2026-03-15 10:30:00")
    private Date addTime;

    @ApiModelProperty(value = "编辑者ID", example = "1")
    private Long editor;

    @ApiModelProperty(value = "编辑者名称", example = "管理员")
    private String editorName;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @ApiModelProperty(value = "编辑时间", example = "2026-03-15 11:00:00")
    private Date editTime;
}