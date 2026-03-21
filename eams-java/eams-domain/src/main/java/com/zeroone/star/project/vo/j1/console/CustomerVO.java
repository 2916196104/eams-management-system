package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * <p>
 * 描述：我的客户视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("我的客户视图对象")
@Data
public class CustomerVO {
    @ApiModelProperty(value = "总客户数", example = "256")
    private Integer totalCustomers;

    @ApiModelProperty(value = "潜在客户数", example = "85")
    private Integer potentialCustomers;

    @ApiModelProperty(value = "跟进中客户数", example = "120")
    private Integer followingCustomers;

    @ApiModelProperty(value = "已报名客户数", example = "48")
    private Integer enrolledCustomers;

    @ApiModelProperty(value = "客户列表", example = "[{'customerId':3001,'customerName':'李明','phone':'13800138000'}]")
    private List<CustomerItem> customerList;

    @Data
    public static class CustomerItem {
        @ApiModelProperty(value = "客户 ID", example = "3001")
        private Integer customerId;

        @ApiModelProperty(value = "客户姓名", example = "李明")
        private String customerName;

        @ApiModelProperty(value = "联系电话", example = "13800138000")
        private String phone;

        @ApiModelProperty(value = "微信/QQ", example = "liming2024")
        private String wechat;

        @ApiModelProperty(value = "意向课程", example = "Java 高级编程")
        private String interestedCourse;

        @ApiModelProperty(value = "客户状态：0-潜在 1-跟进中 2-已报名 3-已流失", example = "1")
        private Integer status;

        @ApiModelProperty(value = "最后跟进时间", example = "2024-03-15 14:30:00")
        private String lastContactTime;
    }
}
