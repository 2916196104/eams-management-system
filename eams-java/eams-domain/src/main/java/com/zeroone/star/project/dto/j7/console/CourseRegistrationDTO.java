package com.zeroone.star.project.dto.j7.console;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：课程报名数据
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
@Data
public class CourseRegistrationDTO {
    @ApiModelProperty(value = "课程ID")
    private Long courseId;              // 课程ID
    @ApiModelProperty(value = "课程名称")
    private String courseName;          // 课程名称

    @ApiModelProperty(value = "总报名次数")
    private Integer totalCount;         // 总报名次数
}
