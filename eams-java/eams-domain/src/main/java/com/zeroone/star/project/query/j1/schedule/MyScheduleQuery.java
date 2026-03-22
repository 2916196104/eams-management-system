package com.zeroone.star.project.query.j1.schedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

import java.util.Date;

/**
 * <p>
 * 描述：我的课表查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("我的课表查询对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
public class MyScheduleQuery extends PageQuery {
    
    /**
     * 课程 ID
     */
    @ApiModelProperty(value = "课程 ID", example = "2001")
    private Long courseId;
    
    /**
     * 课程名称（模糊查询）
     */
    @ApiModelProperty(value = "课程名称（模糊查询）", example = "Java")
    private String courseName;
    
    /**
     * 班级 ID
     */
    @ApiModelProperty(value = "班级 ID", example = "3001")
    private Long classId;
    
    /**
     * 班级名称（模糊查询）
     */
    @ApiModelProperty(value = "班级名称（模糊查询）", example = "Java")
    private String className;
    
    /**
     * 教师 ID
     */
    @ApiModelProperty(value = "教师 ID", example = "501")
    private Long teacherId;
    
    /**
     * 教师姓名（模糊查询）
     */
    @ApiModelProperty(value = "教师姓名（模糊查询）", example = "张")
    private String teacherName;
    
    /**
     * 星期几：1-周一 2-周二 3-周三 4-周四 5-周五 6-周六 7-周日
     */
    @ApiModelProperty(value = "星期几：1-周一 2-周二 3-周三 4-周四 5-周五 6-周六 7-周日", example = "1")
    private Integer weekDay;
    
    /**
     * 课程类型：1-线上课 2-线下课 3-直播课
     */
    @ApiModelProperty(value = "课程类型：1-线上课 2-线下课 3-直播课", example = "2")
    private Integer courseType;
    
    /**
     * 课程状态：0-未开始 1-进行中 2-已结束 3-已调课 4-已取消
     */
    @ApiModelProperty(value = "课程状态：0-未开始 1-进行中 2-已结束 3-已调课 4-已取消", example = "1")
    private Integer status;
    
    /**
     * 开始日期
     */
    @ApiModelProperty(value = "开始日期", example = "2026-03-16")
    private String startDate;
    
    /**
     * 结束日期
     */
    @ApiModelProperty(value = "结束日期", example = "2026-03-31")
    private String endDate;
}
