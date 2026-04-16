package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

/**
 * <p>
 * 省市地区表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("region")
public class Region implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.NONE)
    private Integer id;

    /**
     * 父 id
     */
    private Integer pid;

    /**
     * 简称
     */
    private String shortName;

    /**
     * 名称
     */
    private String name;

    /**
     * 全称
     */
    private String mergerName;

    /**
     * 层级 0 1 2 省市区县
     */
    private Integer level;

    /**
     * 拼音
     */
    private String pinyin;

    /**
     * 长途区号
     */
    private String code;

    /**
     * 邮编
     */
    private String zipCode;

    /**
     * 首字母
     */
    private String first;

    /**
     * 经度
     */
    private String lng;

    /**
     * 纬度
     */
    private String lat;
}
