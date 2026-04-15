package com.zeroone.star.project.dto.j5.courseschedule;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.zeroone.star.project.vo.j5.courseschedule.CourseScheduleSettingVO;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

@Data
public class CourseScheduleDTO {
    @ApiModelProperty(value = "课程编号", example = "1")
    private String id;

    @ApiModelProperty(value = "班级编号", example = "1", required = true)
    private Integer classId;
    @ApiModelProperty(value = "班级名称", example = "Python基础班01期", required = true)
    private String className;

    @ApiModelProperty(value = "老师id", example = "1", required = true)
    private Integer teacherId;
    @ApiModelProperty(value = "上课老师", example = "李文", required = true)
    private String teacherName;

    @ApiModelProperty(value = "助教id", example = "1")
    private Integer assistantId;
    @ApiModelProperty(value = "助教老师", example = "王伟")
    private String assistantName;
    @ApiModelProperty(value = "课程开始时间", example = "2023-01-01 09:00:00", required = true)
    private String startTime;
    @ApiModelProperty(value = "课程结束时间", example = "2023-01-01 10:00:00", required = true)
    private String endTime;
    @ApiModelProperty(value = "学员扣课次数", example = "1")
    private Integer descLessonCount;
    @ApiModelProperty(value = "排课次数", example = "1")
    private Integer times;
    @ApiModelProperty(value = "排除节日", example = "1")
    private String excludeHoliday;


    @ApiModelProperty(value = "课程状态", example = "1")
    private String status;

    @ApiModelProperty( value = "上课时间设置",example = "填写周几上课，上课时间，和下课时间 ")
    private List<CourseScheduleSettingVO> lessonScheduleSettingDtos;

    // 审计字段（对应数据库字段：creator, editor, add_time, edit_time）
    @ApiModelProperty(value = "创建人ID")
    private Long creator;
    
    @ApiModelProperty(value = "更新人ID")
    private Long editor;
    
    @ApiModelProperty(value = "创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime addTime;
    
    @ApiModelProperty(value = "更新时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime editTime;
}
