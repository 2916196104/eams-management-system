package com.zeroone.star.project.query.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：课程报名查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("课程报名查询对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CourseEnrollmentQuery {
    
    /**
     * 课程名称（模糊查询）
     */
    @ApiModelProperty(value = "课程名称（模糊查询）", example = "Java")
    private String courseName;
    
    /**
     * 教师 ID（可选）
     */
    @ApiModelProperty(value = "教师 ID（可选）", example = "2001")
    private Integer teacherId;
    
    /**
     * 报名状态：0-未开始 1-报名中 2-已满 3-已结束（可选）
     */
    @ApiModelProperty(value = "报名状态：0-未开始 1-报名中 2-已满 3-已结束（可选）", example = "1")
    private Integer enrollmentStatus;
}
