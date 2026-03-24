package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：客户信息对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("客户信息对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CustomerDTO {
    
    /**
     * 客户 ID
     */
    @ApiModelProperty(value = "客户 ID", example = "3001")
    private Integer customerId;
    
    /**
     * 客户姓名
     */
    @ApiModelProperty(value = "客户姓名", example = "李明")
    private String customerName;
    
    /**
     * 联系电话
     */
    @ApiModelProperty(value = "联系电话", example = "13800138000")
    private String phone;
    
    /**
     * 微信/QQ
     */
    @ApiModelProperty(value = "微信/QQ", example = "liming2024")
    private String wechat;
    
    /**
     * 邮箱
     */
    @ApiModelProperty(value = "邮箱", example = "liming@example.com")
    private String email;
    
    /**
     * 意向课程
     */
    @ApiModelProperty(value = "意向课程", example = "Java 高级编程")
    private String interestedCourse;
    
    /**
     * 客户来源：0-电话咨询 1-在线咨询 2-朋友推荐 3-活动推广
     */
    @ApiModelProperty(value = "客户来源：0-电话咨询 1-在线咨询 2-朋友推荐 3-活动推广", example = "1")
    private Integer sourceType;
    
    /**
     * 客户状态：0-潜在 1-跟进中 2-已报名 3-已流失
     */
    @ApiModelProperty(value = "客户状态：0-潜在 1-跟进中 2-已报名 3-已流失", example = "1")
    private Integer status;
    
    /**
     * 最后跟进时间
     */
    @ApiModelProperty(value = "最后跟进时间", example = "2024-03-15 14:30:00")
    private String lastContactTime;
    
    /**
     * 备注
     */
    @ApiModelProperty(value = "备注", example = "对 Java 课程很感兴趣，希望了解周末班")
    private String remark;
}
