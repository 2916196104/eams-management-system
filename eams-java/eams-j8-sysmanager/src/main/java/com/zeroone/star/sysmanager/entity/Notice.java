package com.zeroone.star.sysmanager.entity;

import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;
/**
 * <p>
 * 公告
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Data
@TableName("notice")
public class Notice implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * id
     */
    @ApiModelProperty(value = "ID", example = "1")
    @TableId(type = IdType.ASSIGN_UUID)
    private Long id;

    /**
     * 公告标题
     */
    @ApiModelProperty(value = "公告标题", example = "1")
    private String title;

    /**
     * 公告内容
     */
    @ApiModelProperty(value = "公告内容", example = "1")
    private String content;

    @ApiModelProperty(value = "viewNum", example = "1")
    private Integer viewNum;

    /**
     * 创建人
     */
    @ApiModelProperty(value = "创建人", example = "1")
    private Long creator;

    /**
     * 编辑人
     */
    @ApiModelProperty(value = "编辑人", example = "1")
    private Long editor;

    /**
     * 添加时间
     */
    @ApiModelProperty(value = "添加时间", example = "2023-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @ApiModelProperty(value = "编辑时间", example = "2023-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    @ApiModelProperty(value = "创建人", example = "1")
    private Boolean deleted;


}
