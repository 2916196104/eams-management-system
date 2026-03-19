package com.zeroone.star.project.dto.j5.classmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(value = "班级学生传输对象", description = "往班级添加学员的请求参数")
public class ClassDTO {
    @ApiModelProperty(value = "班级id,如果保存必须传，新增不传", example = "1", required = false)
    private Long id;

    @ApiModelProperty(value = "班级名", example = "1班", required = true)
    private String name;

    @ApiModelProperty(value = "分校校区", example = "1校区", required = true)
    private String school;

    @ApiModelProperty(value = "年级", example = "1年级")
    private String grade;

    @ApiModelProperty(value = "班主任", example = "张三", required = true)
    private String teacher;

    @ApiModelProperty(value = "班级预招人数", example = "10", required = true)
    private Integer number;

    @ApiModelProperty(value = "预排课次数", example = "10", required = true)
    private Integer courseCount;

    @ApiModelProperty(value = "默认课程", example = "1课程")
    private String defaultCourse;

    @ApiModelProperty(value = "默认教室", example = "111")
    private String room;


    @ApiModelProperty(value = "计划开课日期", example = "2021-01-01 00:00:00")
    private String createTime;

    @ApiModelProperty(value = "计划结业日期", example = "2025-01-01 00:00:00")
    private String updateTime;

    @ApiModelProperty(value = "排课备注", example = "比别的课程晚两个礼拜开课")
    private String description;

    @ApiModelProperty(value = "班级状态", example = "已结业")
    private String status;

}
