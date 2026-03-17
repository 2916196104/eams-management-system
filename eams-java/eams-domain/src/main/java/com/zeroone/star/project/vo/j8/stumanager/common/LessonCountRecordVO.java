package com.zeroone.star.project.vo.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 消课记录展示对象
 */
@Data
@ApiModel("消课记录展示对象")
public class LessonCountRecordVO {
    @ApiModelProperty(value = "记录ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "学员ID", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "课程ID", example = "1001")
    private Long courseId;

    @ApiModelProperty(value = "课程名称", example = "数学提高班")
    private String courseName;

    @ApiModelProperty(value = "课次ID", example = "2001")
    private Long lessonId;

    @ApiModelProperty(value = "课次标题", example = "第1课时")
    private String lessonTitle;

    @ApiModelProperty(value = "变更课次", example = "-1")
    private Integer changeCount;

    @ApiModelProperty(value = "剩余课次", example = "19")
    private Integer remainingCount;

    @ApiModelProperty(value = "操作人ID", example = "10")
    private Long staffId;

    @ApiModelProperty(value = "操作人姓名", example = "李老师")
    private String staffName;

    @ApiModelProperty(value = "变更阶段", example = "1")
    private Integer stage;

    @ApiModelProperty(value = "变更时间", example = "2026-03-15T10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "备注", example = "正常消课")
    private String remark;
}
