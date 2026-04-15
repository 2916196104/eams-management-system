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
 * 班级
 * @TableName class
 */
@Data
@ApiModel(description = "班级")
@TableName("class")  // 表名是 class，必须指定
public class Class implements Serializable {

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.INPUT)
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;

    /**
     * 班级名
     */
    @NotBlank(message = "[班级名]不能为空")
    @Size(max = 50, message = "编码长度不能超过50")
    @ApiModelProperty("班级名")
    private String name;

    /**
     * 课程
     */
    @NotNull(message = "[课程]不能为空")
    @ApiModelProperty("课程")
    private Long courseId;

    /**
     * 教室
     */
    @ApiModelProperty("教室")
    private Long classroomId;

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
     * 班级负责人
     */
    @ApiModelProperty("班级负责人")
    private Long teacherId;

    /**
     * 排课备注
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("排课备注")
    private String remark;

    /**
     * 是否完结
     */
    @ApiModelProperty("是否完结")
    private Integer beOver;

    /**
     * 完结时间
     */
    @ApiModelProperty("完结时间")
    private Date overTime;

    /**
     * 完结操作人
     */
    @ApiModelProperty("完结操作人")
    private Long overOperator;

    /**
     * 计划开班日期
     */
    @ApiModelProperty("计划开班日期")
    private Date startDate;

    /**
     * 计划结业日期
     */
    @ApiModelProperty("计划结业日期")
    private Date endDate;

    /**
     * 预招人数
     */
    @ApiModelProperty("预招人数")
    private Integer plannedStudentCount;

    /**
     * 预排课次数
     */
    @ApiModelProperty("预排课次数")
    private Integer plannedLessonCount;

    /**
     * 创建者所属学校id
     */
    @ApiModelProperty("创建者所属学校id")
    private Long schoolId;

    /**
     * 创建者所属组织ID
     */
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;

    /**
     * 年级ID
     */
    @ApiModelProperty("年级ID")
    private Integer gradeId;

}
