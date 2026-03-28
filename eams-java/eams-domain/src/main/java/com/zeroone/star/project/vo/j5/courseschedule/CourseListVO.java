package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("课表列表展示VO（含ID与名称）")
public class CourseListVO {

    // 核心ID（用于编辑/操作）
    @ApiModelProperty(value = "课表ID", example = "1001")
    private Long id;

    // 上课时间（展示文本）
    @ApiModelProperty(value = "上课时间", example = "2026-03-22(日) 05:30~05:50")
    private String lessonTimeText;

    // 课程（ID + 名称）
    @ApiModelProperty(value = "课程ID", example = "2001")
    private Long courseId;
    @ApiModelProperty(value = "课程名称", example = "KCMC81740793049482")
    private String courseName;

    // 班级（ID + 名称）
    @ApiModelProperty(value = "班级ID", example = "3001")
    private Long classId;
    @ApiModelProperty(value = "班级名称", example = "与世无争班级")
    private String className;

    // 上课老师（ID列表 + 名称列表，逗号分隔）
    @ApiModelProperty(value = "老师ID列表（逗号分隔）", example = "4001,4002")
    private String teacherIds;
    @ApiModelProperty(value = "老师名称列表（逗号分隔）", example = "JSMCmpoey,张三")
    private String teacherNames;

    // 课程类型
    @ApiModelProperty(value = "课程类型", example = "大班课")
    private String courseType;

    // 助教（ID列表 + 名称列表，逗号分隔）
    @ApiModelProperty(value = "助教ID列表（逗号分隔）", example = "5001,5002")
    private String assistantIds;
    @ApiModelProperty(value = "助教名称列表（逗号分隔）", example = "网,李四")
    private String assistantNames;

    // 教室（ID + 名称）
    @ApiModelProperty(value = "教室ID", example = "6001")
    private Long classroomId;
    @ApiModelProperty(value = "教室名称", example = "国星中学机房")
    private String classroomName;

    // 可预约状态
    @ApiModelProperty(value = "是否可预约", example = "关")
    private String canReserve;

    // 学生相关统计
    @ApiModelProperty(value = "学生数", example = "0")
    private Integer studentCount;
    @ApiModelProperty(value = "限制人数", example = "11")
    private Integer maxStudentCount;
    @ApiModelProperty(value = "签到数", example = "0")
    private Integer checkInCount;
    @ApiModelProperty(value = "到课率", example = "0%")
    private String attendanceRate;

    // 消课相关
    @ApiModelProperty(value = "消课基数", example = "1")
    private Integer decLessonCount;
    @ApiModelProperty(value = "已消课数", example = "0")
    private Integer consumedCount;

    // 上课状态
    @ApiModelProperty(value = "上课情况", example = "未上")
    private String lessonStatus;

}

