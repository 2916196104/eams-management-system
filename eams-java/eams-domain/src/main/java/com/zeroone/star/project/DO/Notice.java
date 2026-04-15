package com.zeroone.star.project.DO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.Date;

/**
 * 公告
 *
 * @TableName notice
 */
@Data
@TableName("notice")
public class Notice implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    @ApiModelProperty("id")
    private Long id;

    @ApiModelProperty("公告标题")
    private String title;

    @ApiModelProperty("公告内容")
    private String content;

    @ApiModelProperty("浏览次数")
    private Integer viewNum;

    @ApiModelProperty("创建人")
    private Long creator;

    @ApiModelProperty("编辑人")
    private Long editor;

    @ApiModelProperty("添加时间")
    private Date addTime;

    @ApiModelProperty("编辑时间")
    private Date editTime;

    @ApiModelProperty("删除标记")
    private Integer deleted;
}
