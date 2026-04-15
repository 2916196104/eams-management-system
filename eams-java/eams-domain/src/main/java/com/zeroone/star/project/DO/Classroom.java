package com.zeroone.star.project.DO;

import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 教室
 * @TableName classroom
 */
@Data
@ApiModel(description = "教室")
@TableName("classroom")
public class Classroom implements Serializable {

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.INPUT)
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;

    /**
     * 教室名
     */
    @Size(max = 50, message = "编码长度不能超过50")
    @ApiModelProperty("教室名")
    private String name;

    /**
     * 位置
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("位置")
    private String address;

    /**
     * 面积平方米
     */
    @ApiModelProperty("面积平方米")
    private Integer area;

    /**
     * 备注
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("备注")
    private String remark;

    /**
     * 创建者
     */
    @ApiModelProperty("创建者")
    private Long creator;

    /**
     * 编辑者
     */
    @ApiModelProperty("编辑者")
    private Long editor;

    /**
     * 创建时间
     */
    @ApiModelProperty("创建时间")
    private Date addTime;

    /**
     * 编辑时间
     */
    @ApiModelProperty("编辑时间")
    private Date editTime;

    /**
     * 删除标记
     */
    @ApiModelProperty("删除标记")
    private Integer deleted;

    /**
     * 创建者所属学校ID
     */
    @ApiModelProperty("创建者所属学校ID")
    private Long schoolId;

    /**
     * 创建者所属组织ID
     */
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;

}