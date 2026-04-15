package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * <p>
 * 描述：我的课表视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("我的课表视图对象")
@Data
public class ScheduleVO {
    @ApiModelProperty(value = "用户 ID", example = "1001")
    private Integer userId;

    @ApiModelProperty(value = "用户类型：0-学生 1-教师", example = "1")
    private Integer userType;

    @ApiModelProperty(value = "周次", example = "5")
    private Integer week;

    @ApiModelProperty(value = "课表数据列表", example = "[{'courseName':'Java','dayOfWeek':1,'period':1}]")
    private List<ScheduleItem> scheduleList;

    @Data
    public static class ScheduleItem {
        @ApiModelProperty(value = "课表 ID", example = "5001")
        private Integer scheduleId;

        @ApiModelProperty(value = "课程 ID", example = "1001")
        private Integer courseId;

        @ApiModelProperty(value = "课程名称", example = "Java 高级编程")
        private String courseName;

        @ApiModelProperty(value = "教师姓名", example = "张老师")
        private String teacherName;

        @ApiModelProperty(value = "教室", example = "教学楼 A-301")
        private String classroom;

        @ApiModelProperty(value = "星期几（1-7）", example = "1")
        private Integer dayOfWeek;

        @ApiModelProperty(value = "节次（1-8）", example = "1")
        private Integer period;

        @ApiModelProperty(value = "开始时间", example = "08:00")
        private String startTime;

        @ApiModelProperty(value = "结束时间", example = "09:40")
        private String endTime;
    }
}
