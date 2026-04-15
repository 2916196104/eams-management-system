package com.zeroone.star.project.query.j1.enrollment;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：本月报名查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("本月报名查询对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
public class MonthlyEnrollmentQuery extends PageQuery {
    
    /**
     * 学员姓名（模糊查询）
     */
    @ApiModelProperty(value = "学员姓名（模糊查询）", example = "张")
    private String studentName;
    
    /**
     * 课程 ID
     */
    @ApiModelProperty(value = "课程 ID", example = "2001")
    private Long courseId;
    
    /**
     * 班级 ID
     */
    @ApiModelProperty(value = "班级 ID", example = "3001")
    private Long classId;
    
    /**
     * 报名状态：0-待审核 1-已通过 2-已拒绝 3-已取消
     */
    @ApiModelProperty(value = "报名状态：0-待审核 1-已通过 2-已拒绝 3-已取消", example = "1")
    private Integer status;
    
    /**
     * 缴费状态：0-未缴费 1-部分缴费 2-已缴费
     */
    @ApiModelProperty(value = "缴费状态：0-未缴费 1-部分缴费 2-已缴费", example = "2")
    private Integer paymentStatus;
    
    /**
     * 开始日期
     */
    @ApiModelProperty(value = "开始日期", example = "2026-03-01")
    private String startDate;
    
    /**
     * 结束日期
     */
    @ApiModelProperty(value = "结束日期", example = "2026-03-31")
    private String endDate;
}
