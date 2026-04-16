package com.zeroone.star.project.entity;

import lombok.Data;

import java.util.Date;

@Data
public class Advertisement {


    //公告id
    private String id;
    //需要上传的图片
    private String cover;
    //公告标题
    private String title;
    //公告内容
    private String content;
    //公告类型
    private Short type;
    //发布人
    private Long creator;
    //修改人
    private Long editor;
    //添加时间
    private Date addTime;
    //修改时间
    private Date editTime;
    //状态
    private Short state;
    //排序
    private Integer sort_num;
    //唯一码
    private String code;
    //是否删除
    private Short deleted;
}
