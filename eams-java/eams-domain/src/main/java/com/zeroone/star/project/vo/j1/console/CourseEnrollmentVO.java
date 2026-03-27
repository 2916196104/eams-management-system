package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * <p>
 * 描述：课程报名统计视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("课程报名统计视图对象")
@Data
public class CourseEnrollmentVO {
    @ApiModelProperty(value = "总课程数", example = "156")
    private Integer totalCourses;

    @ApiModelProperty(value = "报名中课程数", example = "42")
    private Integer enrollingCourses;

    @ApiModelProperty(value = "已满课程数", example = "28")
    private Integer fullCourses;

    @ApiModelProperty(value = "课程报名列表", example = "[{'courseId':1001,'courseName':'Java','enrolledCount':45}]")
    private List<CourseEnrollmentItem> courseList;

    @Data
    public static class CourseEnrollmentItem {
        @ApiModelProperty(value = "课程 ID", example = "1001")
        private Integer courseId;

        @ApiModelProperty(value = "课程名称", example = "Java 高级编程")
        private String courseName;

        @ApiModelProperty(value = "授课教师", example = "张老师")
        private String teacherName;

        @ApiModelProperty(value = "已报名人数", example = "45")
        private Integer enrolledCount;

        @ApiModelProperty(value = "总人数", example = "60")
        private Integer totalCapacity;

        @ApiModelProperty(value = "剩余名额", example = "15")
        private Integer remainingSlots;

        @ApiModelProperty(value = "报名状态：0-未开始 1-报名中 2-已满 3-已结束", example = "1")
        private Integer enrollmentStatus;
    }
}
