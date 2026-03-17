package com.zeroone.star.project.query.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：我的客户查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("我的客户查询对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CustomerQuery {
    
    /**
     * 客户姓名（模糊查询）
     */
    @ApiModelProperty(value = "客户姓名（模糊查询）", example = "李")
    private String customerName;
    
    /**
     * 联系电话（可选）
     */
    @ApiModelProperty(value = "联系电话（可选）", example = "13800138000")
    private String phone;
    
    /**
     * 客户状态：0-潜在 1-跟进中 2-已报名 3-已流失（可选）
     */
    @ApiModelProperty(value = "客户状态：0-潜在 1-跟进中 2-已报名 3-已流失（可选）", example = "1")
    private Integer status;
    
    /**
     * 意向课程（可选）
     */
    @ApiModelProperty(value = "意向课程（可选）", example = "Java")
    private String interestedCourse;
}
