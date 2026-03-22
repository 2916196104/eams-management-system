package com.zeroone.star.project.vo.j5.courseplan;


import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/*
* 描述：分页查询展示对象
* */
@Data
public class SchedulePlanVO {
    @ApiModelProperty(value = "排课计划id",required = false, example = "1")
    private Long id;

    @ApiModelProperty(value = "课表是否生成 默认0",required = false,example = "0 未生成 1 已生成")
    private Integer state;

    @ApiModelProperty(value = "冲突的id列表 空字符表示无冲突 null是未检查" ,required = false,example = "无冲突 or 8个冲突")
    private String conflictIds;

    @ApiModelProperty(value = "班级名称",required = false,example = "信息特长班")
    private String className;

    @ApiModelProperty(value = "课程名称",required = false,example = "C语言")
    private String courseName;

    @ApiModelProperty(value = "上课老师名称列表",required = false,example = "张三，李四")
    private String teacherNames;

    @ApiModelProperty(value = "助教老师列表",example = "王五，赵六")
    private String assistantTeacherNames;

    @ApiModelProperty(value = "开始时间",example = "2021-01-01")
    private LocalDateTime startDate;

    @ApiModelProperty(value = "结束时间",example = "2021-01-01")
    private LocalDateTime endDate;

    @ApiModelProperty(value = "上课时间",example = "四 05:00~05:15")
    private String date;

    @ApiModelProperty(value = "计划课次",example = "80")
    private Integer times;

    @ApiModelProperty(value = "已生成课次",example = "2")
    private Integer decLessonCount;

    @ApiModelProperty(value = "消课基数，默认值为1",example = "1")
    private Integer decCount;

    @ApiModelProperty(value = "是否排除节假日 默认值为0",example = "0 不排除 1 排除")
    private Integer excludeHoliday;

    @ApiModelProperty(value = "教室名称，用于修改排课计划时的页面回显",example = "教室1")
    private String classRoomName;

}
