package com.zeroone.star.project.DO;

import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.math.BigDecimal;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
* 课时老师关联表
* @TableName lesson_teacher
*/
@Data
@ApiModel(description = "课时老师关联表")
@TableName("lesson_teacher")
public class LessonTeacher implements Serializable {

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.INPUT)
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;

    /**
     * 课程id
     */
    @NotNull(message = "[课程id]不能为空")
    @ApiModelProperty("课程id")
    private Long lessonId;

    /**
     * 老师ID（对应SQL：teacher_id）
     */
    @NotNull(message = "[老师id]不能为空")
    @ApiModelProperty("老师id")
    private Long teacherId;

    /**
     * 课时费
     */
    @ApiModelProperty("课时费")
    private BigDecimal commission;

    /**
     * 1上课老师 2助教
     */
    @NotNull(message = "[1上课老师2助教]不能为空")
    @ApiModelProperty("1上课老师 2助教")
    private Integer typeNum;

}
