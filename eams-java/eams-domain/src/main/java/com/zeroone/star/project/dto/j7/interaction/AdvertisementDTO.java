package com.zeroone.star.project.dto.j7.interaction;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.Date;

/*
 * 公告列表查询对象
 * @author 薛定猫
 * @date 2026/3/16
 * */
@Data
public class AdvertisementDTO implements Serializable {

    @ApiModelProperty(value = "公告id，如果是修改必须传id，新增和删除不需要",example = "1")
    private String id;

    @ApiModelProperty(value = "发布人",example = "1")
    private Long creator;

    @ApiModelProperty(value = "公告标题",required = true,example = "新版上线公告")
    private String title;

    @ApiModelProperty(value = "公告内容",example = "上课")
    private String content;

    @ApiModelProperty(value = "公告类型",example = "1")
    private Short type;

    @ApiModelProperty(value = "图片地址",example = "http://localhost:20001/upload/test01.jpg")
    private String cover;

    @ApiModelProperty(value = "添加时间",example = "2026-03-16 18:34:30")
    private Date addTime;

    @ApiModelProperty(value = "修改时间",example = "2026-03-16 18:34:30")
    private Date editTime;

    @ApiModelProperty(value = "编辑人",example = "1")
    private Long editor;

    @ApiModelProperty(value = "状态码",example = "1")
    private Short state;

    @ApiModelProperty(value = "排序",example = "1")
    private Integer sort_num;

    @ApiModelProperty(value = "唯一码",example = "1234")
    private String code;

    @ApiModelProperty(value = "是否删除",example = "1")
    private Short deleted;

}
