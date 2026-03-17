package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;

/**
 * <p>
 * 描述：本月报名统计数据对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("本月报名统计数据对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class MonthEnrollmentDTO {
    
    /**
     * 日期
     */
    @ApiModelProperty(value = "日期", example = "2024-03-01")
    private Date date;
    
    /**
     * 报名数量
     */
    @ApiModelProperty(value = "报名数量", example = "15")
    private Integer enrollmentCount;
    
    /**
     * 报名人数（按天统计）
     */
    @ApiModelProperty(value = "报名人数", example = "12")
    private Integer studentCount;
    
    /**
     * 课程名称
     */
    @ApiModelProperty(value = "课程名称", example = "Java 高级编程")
    private String courseName;
    
    /**
     * 班级名称
     */
    @ApiModelProperty(value = "班级名称", example = "2024 春-Java-01 班")
    private String className;
}
