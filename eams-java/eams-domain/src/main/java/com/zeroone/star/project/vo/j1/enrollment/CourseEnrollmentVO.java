package com.zeroone.star.project.vo.j1.enrollment;

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
 * 描述：课程报名显示对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("课程报名显示对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class CourseEnrollmentVO {
    
    /**
     * 报名编号
     */
    @ApiModelProperty(value = "报名编号", example = "1")
    private Long id;
    
    /**
     * 学员姓名
     */
    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;
    
    /**
     * 学员手机号（脱敏）
     */
    @ApiModelProperty(value = "学员手机号（脱敏）", example = "138****8000")
    private String studentPhone;
    
    /**
     * 学员邮箱
     */
    @ApiModelProperty(value = "学员邮箱", example = "zhang****@example.com")
    private String studentEmail;
    
    /**
     * 课程名称
     */
    @ApiModelProperty(value = "课程名称", example = "Java 高级开发")
    private String courseName;
    
    /**
     * 课程类型：1-线上课 2-线下课 3-直播课
     */
    @ApiModelProperty(value = "课程类型：1-线上课 2-线下课 3-直播课", example = "2")
    private Integer courseType;
    
    /**
     * 课程类型名称
     */
    @ApiModelProperty(value = "课程类型名称", example = "线下课")
    private String courseTypeName;
    
    /**
     * 课程开始时间
     */
    @ApiModelProperty(value = "课程开始时间", example = "2026-04-01 09:00:00")
    private Date courseStartTime;
    
    /**
     * 课程结束时间
     */
    @ApiModelProperty(value = "课程结束时间", example = "2026-06-30 17:00:00")
    private Date courseEndTime;
    
    /**
     * 班级名称
     */
    @ApiModelProperty(value = "班级名称", example = "Java2301 班")
    private String className;
    
    /**
     * 班主任姓名
     */
    @ApiModelProperty(value = "班主任姓名", example = "李老师")
    private String headTeacher;
    
    /**
     * 剩余名额
     */
    @ApiModelProperty(value = "剩余名额", example = "5")
    private Integer remainingSeats;
    
    /**
     * 实际支付金额
     */
    @ApiModelProperty(value = "实际支付金额", example = "9800.00")
    private BigDecimal actualAmount;
    
    /**
     * 报名状态：0-待审核 1-已通过 2-已拒绝 3-已取消 4-学习中 5-已完成 6-已退学
     */
    @ApiModelProperty(value = "报名状态：0-待审核 1-已通过 2-已拒绝 3-已取消 4-学习中 5-已完成 6-已退学", example = "1")
    private Integer status;
    
    /**
     * 状态名称
     */
    @ApiModelProperty(value = "状态名称", example = "已通过")
    private String statusName;
    
    /**
     * 报名时间
     */
    @ApiModelProperty(value = "报名时间", example = "2026-03-01 10:30:00")
    private Date enrollmentTime;
    
    /**
     * 审核时间
     */
    @ApiModelProperty(value = "审核时间", example = "2026-03-02 14:20:00")
    private Date auditTime;
    
    /**
     * 审核人姓名
     */
    @ApiModelProperty(value = "审核人姓名", example = "王老师")
    private String auditorName;
    
    /**
     * 审核备注
     */
    @ApiModelProperty(value = "审核备注", example = "资料齐全，同意报名")
    private String auditRemark;
    
    /**
     * 来源渠道：1-官网 2-公众号 3-朋友推荐 4-电话咨询 5-校园宣讲 6-其他
     */
    @ApiModelProperty(value = "来源渠道：1-官网 2-公众号 3-朋友推荐 4-电话咨询 5-校园宣讲 6-其他", example = "1")
    private Integer sourceChannel;
    
    /**
     * 来源渠道名称
     */
    @ApiModelProperty(value = "来源渠道名称", example = "官网")
    private String sourceChannelName;
}
