package com.zeroone.star.project.DO;

import javax.validation.constraints.NotBlank;
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
 * 课程表
 * @TableName lesson
 */
@Data
@ApiModel(description = "课程表")
@TableName("lesson")
public class Lesson implements Serializable {

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.INPUT)
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;

    /**
     * 课程标题
     */
    @NotBlank(message = "[课程标题]不能为空")
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("课程标题")
    private String title;

    /**
     * 课节数 第几节课
     */
    @ApiModelProperty("课节数 第几节课")
    private Integer sn;

    /**
     * 课程id
     */
    @NotNull(message = "[课程id]不能为空")
    @ApiModelProperty("课程id")
    private Long courseId;

    /**
     * 编排计划id
     */
    @ApiModelProperty("编排计划id")
    private Long scheduleId;

    /**
     * 班级id
     */
    @ApiModelProperty("班级id")
    private Long classId;

    /**
     * 教室id
     */
    @ApiModelProperty("教室id")
    private Long roomId;

    /**
     * 上课日期
     */
    @ApiModelProperty("上课日期")
    private Date date;

    /**
     * 开始时间
     */
    @ApiModelProperty("开始时间")
    private Date startTime;

    /**
     * 结束时间
     */
    @ApiModelProperty("结束时间")
    private Date endTime;

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
     * 添加时间
     */
    @ApiModelProperty("添加时间")
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
     * 应扣课次数
     */
    @ApiModelProperty("应扣课次数")
    private Integer decCount;

    /**
     * 备注
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("备注")
    private String remark;

    /**
     * 授课方式
     */
    @ApiModelProperty("授课方式")
    private Integer teachType;

    /**
     * 是否开启试听
     */
    @ApiModelProperty("是否开启试听")
    private Integer onTrial;

    /**
     * 试听结果
     */
    @ApiModelProperty("试听结果")
    private String trialResult;

    /**
     * 课次状态
     */
    @ApiModelProperty("课次状态")
    private Integer state;

    /**
     * 结课时间
     */
    @ApiModelProperty("结课时间")
    private Date closeTime;

    /**
     * 结课人
     */
    @ApiModelProperty("结课人")
    private Long closeOperator;

    /**
     * 主讲人(只用于数据权限)
     */
    @ApiModelProperty("主讲人(只用于数据权限)")
    private Long teacherId;

    /**
     * 是否开放预约
     */
    @ApiModelProperty("是否开放预约")
    private Integer bookable;

    /**
     * 老师所属学校ID
     */
    @ApiModelProperty("老师所属学校ID")
    private Long schoolId;

    /**
     * 创建者所属组织ID
     */
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;

}
