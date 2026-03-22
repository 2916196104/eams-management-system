package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;


@Data
@ApiModel("课程详情弹窗VO")
public class CourseDetailVO {

    // 核心信息（展示用）
    @ApiModelProperty(value = "标题", example = "足球")
    private String title;

    @ApiModelProperty(value = "课程名称", example = "足球")
    private String courseName;
    @ApiModelProperty(value = "课程编号", example = "001")
    private String courseNo;

    @ApiModelProperty(value = "班级名称", example = "与世无争班级")
    private String className;
    @ApiModelProperty(value = "班级编号", example = "001")
    private String classNo;

    @ApiModelProperty(value = "课程类型", example = "大班课")
    private String courseType;

    @ApiModelProperty(value = "上课时间文本", example = "2026-03-22(日) 15:25 ~ 15:30")
    private String lessonTimeText;

    @ApiModelProperty(value = "教室名称", example = "国星中学机房")
    private String classroomName;
    @ApiModelProperty(value = "教室编号", example = "001")
    private String classroomNo;

    @ApiModelProperty(value = "老师名称", example = "JSMCmpoey")
    private String teacherName;
    @ApiModelProperty(value = "老师编号", example = "001")
    private String teacherNo;

    @ApiModelProperty(value = "助教名称", example = "网")
    private String assistantName;
    @ApiModelProperty(value = "助教编号", example = "001")
    private String assistantNo;

    @ApiModelProperty(value = "实到/应到", example = "2 / 7")
    private String attendInfo;

    @ApiModelProperty(value = "消课基数", example = "1")
    private Integer decLessonCount;

    @ApiModelProperty(value = "是否可预约", example = "是")
    private String canReserve;

    @ApiModelProperty(value = "状态", example = "进行中")
    private String status;
}
