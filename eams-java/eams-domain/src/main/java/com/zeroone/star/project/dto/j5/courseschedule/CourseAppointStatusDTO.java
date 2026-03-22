package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：课程状态传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 無名
 * @version 1.0.0
 */

@Data
public class CourseAppointStatusDTO {
    @ApiModelProperty( value = "课程编号", example = "1")
    private String id;
    @ApiModelProperty( value = "课程预约开关", example = "1")
    private String status;
}