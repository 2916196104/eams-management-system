package com.zeroone.star.project.Do.j5.classmanager;


import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("class_student")
@ApiModel(description = "班级学生关联表")
public class ClassStudentDO {

    @TableId(type = IdType.AUTO)
    @ApiModelProperty(value = "主键", example = "1")
    private Long id;

    @ApiModelProperty(value = "班级ID", example = "5")
    private Long classId;

    @ApiModelProperty(value = "学生ID", example = "10")
    private Long studentId;

    @ApiModelProperty(value = "添加时间", example = "2023-03-01 10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "创建人", example = "1")
    private Long creator;

    @ApiModelProperty(value = "加入原因", example = "1")
    private Integer reason;

    @TableLogic
    @ApiModelProperty(value = "删除标记", example = "false")
    private Boolean deleted;

    @ApiModelProperty(value = "备注信息", example = "备注")
    private String remark;

    @ApiModelProperty(value = "默认消费课程ID", example = "8")
    private Long consumeCourseId;
}