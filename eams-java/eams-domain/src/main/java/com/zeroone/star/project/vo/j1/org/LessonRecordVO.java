package com.zeroone.star.project.vo.j1.org;

import io.swagger.annotations.ApiModelProperty;

import io.swagger.annotations.ApiModel;
import lombok.Data;

/**
 * <p>
 * 描述：员工授课记录展示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author chichu
 * @version 1.0.0
 */


@Data
@ApiModel(value = "LessonRecordVO", description = "授课记录VO")
public class LessonRecordVO {
//
//    @ApiModelProperty(value = "课次ID", example = "5001")
//    private Long id;

    @ApiModelProperty(value = "上课时间", example = "2026-03-19(四) 20:53~20:53")
    private String lessonTime;

    @ApiModelProperty(value = "所属课程", example = "KCMC81740793049482", required = true)
    private String courseName;

    @ApiModelProperty(value = "班级名称", example = "测试", required = true)
    private String className;

    @ApiModelProperty(value = "上课老师", example = "王伟大,翠花", required = true)
    private String teacherNames;

    @ApiModelProperty(value = "助教", example = "JSM Cnuzjy,教练-清北信奥")
    private String assistantNames;

    @ApiModelProperty(value = "教室", example = "G102")
    private String classroomName;

    @ApiModelProperty(value = "已取消课数", example = "0")
    private Integer canceledCount;

    @ApiModelProperty(value = "上课情况", example = "未上")
    private String lessonStatus;

    @ApiModelProperty(value = "状态", example = "进行中")
    private String stateName;
}