package com.zeroone.star.project.dto.j1.enrollment;

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
 * 描述：本月报名数据传输对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("本月报名数据对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class MonthlyEnrollmentDTO {
    
    /**
     * 报名编号
     */
    @ApiModelProperty(value = "报名编号", example = "1")
    private Long id;
    
    /**
     * 学员 ID
     */
    @ApiModelProperty(value = "学员 ID", example = "1001")
    private Long studentId;
    
    /**
     * 学员姓名
     */
    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;
    
    /**
     * 课程 ID
     */
    @ApiModelProperty(value = "课程 ID", example = "2001")
    private Long courseId;
    
    /**
     * 课程名称
     */
    @ApiModelProperty(value = "课程名称", example = "Java 高级开发")
    private String courseName;
    
    /**
     * 班级 ID
     */
    @ApiModelProperty(value = "班级 ID", example = "3001")
    private Long classId;
    
    /**
     * 班级名称
     */
    @ApiModelProperty(value = "班级名称", example = "Java2301 班")
    private String className;
    
    /**
     * 报名时间
     */
    @ApiModelProperty(value = "报名时间", example = "2026-03-01 10:30:00")
    private Date enrollmentTime;
    
    /**
     * 报名状态：0-待审核 1-已通过 2-已拒绝 3-已取消
     */
    @ApiModelProperty(value = "报名状态：0-待审核 1-已通过 2-已拒绝 3-已取消", example = "1")
    private Integer status;
    
    /**
     * 报名费用
     */
    @ApiModelProperty(value = "报名费用", example = "9800.00")
    private BigDecimal fee;
    
    /**
     * 已缴金额
     */
    @ApiModelProperty(value = "已缴金额", example = "9800.00")
    private BigDecimal paidAmount;
    
    /**
     * 备注
     */
    @ApiModelProperty(value = "备注", example = "首次报名")
    private String remark;
}
