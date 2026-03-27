package com.zeroone.star.project.DO;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;
import java.util.Date;

import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.hibernate.validator.constraints.Length;

/**
 * 科目表
 * @TableName subject
 */
@TableName("subject")
@ApiModel(description = "科目表")
@Data
public class Subject implements Serializable {
    /**
     * 主键
     */
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;
    /**
     * 科目
     */
    @NotBlank(message = "[科目]不能为空")
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("科目")
    @Length(max = 255, message = "编码长度不能超过255")
    private String name;
    /**
     * 简介
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("简介")
    @Length(max = 255, message = "编码长度不能超过255")
    private String info;
    /**
     * 创建人
     */
    @ApiModelProperty("创建人")
    private Long creator;
    /**
     * 编辑者
     */
    @ApiModelProperty("编辑者")
    private Long editor;
    /**
     * 新增时间
     */
    @ApiModelProperty("新增时间")
    private Date addTime;
    /**
     * 修改时间
     */
    @ApiModelProperty("修改时间")
    private Date editTime;
    /**
     * 删除标记
     */
    @ApiModelProperty("删除标记")
    private Integer deleted;
    /**
     * 排序值
     */
    @ApiModelProperty("排序值")
    private Integer sortNum;
    /**
     * 创建者所属组织ID
     */
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;
}