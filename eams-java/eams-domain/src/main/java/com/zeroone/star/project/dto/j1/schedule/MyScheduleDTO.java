package com.zeroone.star.project.dto.j1.schedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;

/**
 * <p>
 * 描述：我的课表数据传输对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("我的课表数据对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class MyScheduleDTO {
    
    /**
     * 课表 ID
     */
    @ApiModelProperty(value = "课表 ID", example = "1")
    private Long id;
    
    /**
     * 学员 ID
     */
    @ApiModelProperty(value = "学员 ID", example = "1001")
    private Long studentId;
    
    /**
     * 课程 ID
     */
    @ApiModelProperty(value = "课程 ID", example = "2001")
    private Long courseId;
    
    /**
     * 课程名称
     */
    @ApiModelProperty(value = "课程名称", example = "Java 高级开发")
    private String courseName;
    
    /**
     * 课程类型：1-线上课 2-线下课 3-直播课
     */
    @ApiModelProperty(value = "课程类型：1-线上课 2-线下课 3-直播课", example = "2")
    private Integer courseType;
    
    /**
     * 班级 ID
     */
    @ApiModelProperty(value = "班级 ID", example = "3001")
    private Long classId;
    
    /**
     * 班级名称
     */
    @ApiModelProperty(value = "班级名称", example = "Java2301 班")
    private String className;
    
    /**
     * 教室 ID
     */
    @ApiModelProperty(value = "教室 ID", example = "101")
    private Long classroomId;
    
    /**
     * 教室名称
     */
    @ApiModelProperty(value = "教室名称", example = "第一教学楼 301")
    private String classroomName;
    
    /**
     * 教师 ID
     */
    @ApiModelProperty(value = "教师 ID", example = "501")
    private Long teacherId;
    
    /**
     * 教师姓名
     */
    @ApiModelProperty(value = "教师姓名", example = "张老师")
    private String teacherName;
    
    /**
     * 星期几：1-周一 2-周二 3-周三 4-周四 5-周五 6-周六 7-周日
     */
    @ApiModelProperty(value = "星期几：1-周一 2-周二 3-周三 4-周四 5-周五 6-周六 7-周日", example = "1")
    private Integer weekDay;
    
    /**
     * 第几节课：1-第 1 节 2-第 2 节...8-第 8 节
     */
    @ApiModelProperty(value = "第几节课：1-第 1 节 2-第 2 节...8-第 8 节", example = "1")
    private Integer lessonOrder;
    
    /**
     * 上课时间
     */
    @ApiModelProperty(value = "上课时间", example = "2026-03-16 08:00:00")
    private Date scheduleTime;
    
    /**
     * 下课时间
     */
    @ApiModelProperty(value = "下课时间", example = "2026-03-16 09:40:00")
    private Date endTime;
    
    /**
     * 周次
     */
    @ApiModelProperty(value = "周次", example = "第 5 周")
    private String weekNumber;
    
    /**
     * 课程状态：0-未开始 1-进行中 2-已结束 3-已调课 4-已取消
     */
    @ApiModelProperty(value = "课程状态：0-未开始 1-进行中 2-已结束 3-已调课 4-已取消", example = "1")
    private Integer status;
    
    /**
     * 备注
     */
    @ApiModelProperty(value = "备注", example = "正常上课")
    private String remark;
}
