package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：课程报名统计对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("课程报名统计对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CourseEnrollmentDTO {
    
    /**
     * 课程 ID
     */
    @ApiModelProperty(value = "课程 ID", example = "1001")
    private Integer courseId;
    
    /**
     * 课程名称
     */
    @ApiModelProperty(value = "课程名称", example = "Java 高级编程")
    private String courseName;
    
    /**
     * 授课教师
     */
    @ApiModelProperty(value = "授课教师", example = "张老师")
    private String teacherName;
    
    /**
     * 总人数
     */
    @ApiModelProperty(value = "总人数", example = "60")
    private Integer totalCapacity;
    
    /**
     * 已报名人数
     */
    @ApiModelProperty(value = "已报名人数", example = "45")
    private Integer enrolledCount;
    
    /**
     * 剩余名额
     */
    @ApiModelProperty(value = "剩余名额", example = "15")
    private Integer remainingSlots;
    
    /**
     * 报名状态：0-未开始 1-报名中 2-已满 3-已结束
     */
    @ApiModelProperty(value = "报名状态：0-未开始 1-报名中 2-已满 3-已结束", example = "1")
    private Integer enrollmentStatus;
}
