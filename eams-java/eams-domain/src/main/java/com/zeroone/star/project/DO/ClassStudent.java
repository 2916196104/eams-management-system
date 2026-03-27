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
 * 班级学员表
 * @TableName class_student
 */
@Data
@ApiModel(description = "班级学员表")
@TableName("class_student")
public class ClassStudent implements Serializable {

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.INPUT)
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;

    /**
     * 班级id
     */
    @NotNull(message = "[班级id]不能为空")
    @ApiModelProperty("班级id")
    private Long classId;

    /**
     * 学生id
     */
    @NotNull(message = "[学生id]不能为空")
    @ApiModelProperty("学生id")
    private Long studentId;

    /**
     * 添加时间
     */
    @ApiModelProperty("添加时间")
    private Date addTime;

    /**
     * 创建人
     */
    @ApiModelProperty("创建人")
    private Long creator;

    /**
     * 加入原因
     */
    @ApiModelProperty("加入原因")
    private Integer reason;

    /**
     * 删除标记
     */
    @ApiModelProperty("删除标记")
    private Integer deleted;

    /**
     * 备注信息
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("备注信息")
    private String remark;

    /**
     * 默认消费课程
     */
    @NotNull(message = "[默认消费课程]不能为空")
    @ApiModelProperty("默认消费课程")
    private Long consumeCourseId;

}