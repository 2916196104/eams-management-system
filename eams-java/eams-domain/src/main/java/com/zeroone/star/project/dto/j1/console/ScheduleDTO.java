package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：课表信息对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("课表信息对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class ScheduleDTO {
    
    /**
     * 课表 ID
     */
    @ApiModelProperty(value = "课表 ID", example = "5001")
    private Integer scheduleId;
    
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
     * 教师 ID
     */
    @ApiModelProperty(value = "教师 ID", example = "2001")
    private Integer teacherId;
    
    /**
     * 教师姓名
     */
    @ApiModelProperty(value = "教师姓名", example = "张老师")
    private String teacherName;
    
    /**
     * 教室
     */
    @ApiModelProperty(value = "教室", example = "教学楼 A-301")
    private String classroom;
    
    /**
     * 星期几（1-7）
     */
    @ApiModelProperty(value = "星期几（1-7）", example = "1")
    private Integer dayOfWeek;
    
    /**
     * 节次（1-8）
     */
    @ApiModelProperty(value = "节次（1-8）", example = "1")
    private Integer period;
    
    /**
     * 开始时间
     */
    @ApiModelProperty(value = "开始时间", example = "08:00")
    private String startTime;
    
    /**
     * 结束时间
     */
    @ApiModelProperty(value = "结束时间", example = "09:40")
    private String endTime;
}
