package com.zeroone.star.project.DO.j5.classmanager;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.github.classgraph.json.Id;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel(description = "学员实体")

/*
* 测试使用
* */
@TableName("student")


public class Student {

    @Id
    @ApiModelProperty(value = "学员ID", example = "1")
    @TableId
    private Long id;


    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String name;

    @TableField("student_no")
    @ApiModelProperty(value = "学号", example = "20230001")
    private String studentNo;

    @ApiModelProperty(value = "所属班级ID", example = "5")
    @TableField("class_id")
    private Long classId;
    @ApiModelProperty(value = "性别 1男 2女", example = "1")
    private Integer gender;

    @ApiModelProperty(value = "联系电话", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "添加时间", example = "2023-01-01 10:00:00")
    @TableField("add_time")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "删除标记", example = "false")
    private Boolean deleted;
}
