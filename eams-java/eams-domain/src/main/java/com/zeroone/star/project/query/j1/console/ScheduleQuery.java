package com.zeroone.star.project.query.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：我的课表查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("我的课表查询对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class ScheduleQuery {
    
    /**
     * 用户 ID（教师或学生 ID）
     */
    @ApiModelProperty(value = "用户 ID（教师或学生 ID）", example = "1001")
    private Integer userId;
    
    /**
     * 用户类型：0-学生 1-教师
     */
    @ApiModelProperty(value = "用户类型：0-学生 1-教师", example = "1")
    private Integer userType;
    
    /**
     * 周次（可选，默认当前周）
     */
    @ApiModelProperty(value = "周次（可选，默认当前周）", example = "5")
    private Integer week;
}
