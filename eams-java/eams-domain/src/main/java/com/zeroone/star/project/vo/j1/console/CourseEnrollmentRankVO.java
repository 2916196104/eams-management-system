package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：课程报名金额排行视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("课程报名金额排行视图对象")
@Data
public class CourseEnrollmentRankVO {
    
    @ApiModelProperty(value = "课程名称", example = "Java基础班")
    private String courseName;
    
    @ApiModelProperty(value = "报名金额", example = "2999997")
    private Double amount;
}
