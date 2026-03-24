package com.zeroone.star.project.vo.j1.customer;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.math.BigDecimal;
import java.util.Date;

/**
 * <p>
 * 描述：我的客户显示对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("我的客户显示对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class MyCustomerVO {
    
    /**
     * 客户 ID
     */
    @ApiModelProperty(value = "客户 ID", example = "1")
    private Long id;
    
    /**
     * 客户姓名
     */
    @ApiModelProperty(value = "客户姓名", example = "李先生")
    private String customerName;
    
    /**
     * 客户手机号（脱敏）
     */
    @ApiModelProperty(value = "客户手机号（脱敏）", example = "138****8000")
    private String customerPhone;
    
    /**
     * 客户邮箱（脱敏）
     */
    @ApiModelProperty(value = "客户邮箱（脱敏）", example = "lis****@example.com")
    private String customerEmail;
    
    /**
     * 客户性别：0-未知 1-男 2-女
     */
    @ApiModelProperty(value = "客户性别：0-未知 1-男 2-女", example = "1")
    private Integer gender;
    
    /**
     * 性别名称
     */
    @ApiModelProperty(value = "性别名称", example = "男")
    private String genderName;
    
    /**
     * 客户年龄
     */
    @ApiModelProperty(value = "客户年龄", example = "25")
    private Integer age;
    
    /**
     * 学历：1-高中及以下 2-大专 3-本科 4-硕士及以上
     */
    @ApiModelProperty(value = "学历：1-高中及以下 2-大专 3-本科 4-硕士及以上", example = "3")
    private Integer education;
    
    /**
     * 学历名称
     */
    @ApiModelProperty(value = "学历名称", example = "本科")
    private String educationName;
    
    /**
     * 意向课程名称
     */
    @ApiModelProperty(value = "意向课程名称", example = "Java 高级开发")
    private String intentionCourseName;
    
    /**
     * 客户来源：1-官网 2-公众号 3-朋友推荐 4-电话咨询 5-校园宣讲 6-其他
     */
    @ApiModelProperty(value = "客户来源：1-官网 2-公众号 3-朋友推荐 4-电话咨询 5-校园宣讲 6-其他", example = "1")
    private Integer sourceChannel;
    
    /**
     * 来源渠道名称
     */
    @ApiModelProperty(value = "来源渠道名称", example = "官网")
    private String sourceChannelName;
    
    /**
     * 客户级别：A-高意向 B-中意向 C-低意向 D-无效
     */
    @ApiModelProperty(value = "客户级别：A-高意向 B-中意向 C-低意向 D-无效", example = "A")
    private String customerLevel;
    
    /**
     * 客户级别名称
     */
    @ApiModelProperty(value = "客户级别名称", example = "高意向")
    private String customerLevelName;
    
    /**
     * 跟进状态：0-未分配 1-待跟进 2-跟进中 3-已报名 4-已流失 5-已冻结
     */
    @ApiModelProperty(value = "跟进状态：0-未分配 1-待跟进 2-跟进中 3-已报名 4-已流失 5-已冻结", example = "2")
    private Integer followStatus;
    
    /**
     * 跟进状态名称
     */
    @ApiModelProperty(value = "跟进状态名称", example = "跟进中")
    private String followStatusName;
    
    /**
     * 下次跟进时间
     */
    @ApiModelProperty(value = "下次跟进时间", example = "2026-03-17 10:00:00")
    private Date nextFollowTime;
    
    /**
     * 最后一次跟进时间
     */
    @ApiModelProperty(value = "最后一次跟进时间", example = "2026-03-16 15:30:00")
    private Date lastFollowTime;
    
    /**
     * 最后一次跟进内容
     */
    @ApiModelProperty(value = "最后一次跟进内容", example = "客户表示考虑中，下周回复")
    private String lastFollowContent;
    
    /**
     * 预计报名时间
     */
    @ApiModelProperty(value = "预计报名时间", example = "2026-03-25")
    private Date estimatedEnrollmentTime;
    
    /**
     * 预算金额
     */
    @ApiModelProperty(value = "预算金额", example = "10000.00")
    private BigDecimal budgetAmount;
    
    /**
     * 销售顾问姓名
     */
    @ApiModelProperty(value = "销售顾问姓名", example = "王销售")
    private String salesName;
    
    /**
     * 创建时间
     */
    @ApiModelProperty(value = "创建时间", example = "2026-03-10 09:00:00")
    private Date createTime;
    
    /**
     * 更新时间
     */
    @ApiModelProperty(value = "更新时间", example = "2026-03-16 15:30:00")
    private Date updateTime;
}
