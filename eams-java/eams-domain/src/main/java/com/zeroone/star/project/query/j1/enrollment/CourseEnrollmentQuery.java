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
 * 描述：课程报名查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("课程报名查询对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
public class CourseEnrollmentQuery extends PageQuery {
    
    /**
     * 学员姓名（模糊查询）
     */
    @ApiModelProperty(value = "学员姓名（模糊查询）", example = "张")
    private String studentName;
    
    /**
     * 学员手机号
     */
    @ApiModelProperty(value = "学员手机号", example = "13800138000")
    private String studentPhone;
    
    /**
     * 课程 ID
     */
    @ApiModelProperty(value = "课程 ID", example = "2001")
    private Long courseId;
    
    /**
     * 课程名称（模糊查询）
     */
    @ApiModelProperty(value = "课程名称（模糊查询）", example = "Java")
    private String courseName;
    
    /**
     * 班级 ID
     */
    @ApiModelProperty(value = "班级 ID", example = "3001")
    private Long classId;
    
    /**
     * 班级名称（模糊查询）
     */
    @ApiModelProperty(value = "班级名称（模糊查询）", example = "Java")
    private String className;
    
    /**
     * 课程类型：1-线上课 2-线下课 3-直播课
     */
    @ApiModelProperty(value = "课程类型：1-线上课 2-线下课 3-直播课", example = "2")
    private Integer courseType;
    
    /**
     * 报名状态：0-待审核 1-已通过 2-已拒绝 3-已取消 4-学习中 5-已完成 6-已退学
     */
    @ApiModelProperty(value = "报名状态：0-待审核 1-已通过 2-已拒绝 3-已取消 4-学习中 5-已完成 6-已退学", example = "1")
    private Integer status;
    
    /**
     * 来源渠道：1-官网 2-公众号 3-朋友推荐 4-电话咨询 5-校园宣讲 6-其他
     */
    @ApiModelProperty(value = "来源渠道：1-官网 2-公众号 3-朋友推荐 4-电话咨询 5-校园宣讲 6-其他", example = "1")
    private Integer sourceChannel;
    
    /**
     * 开始日期（报名时间）
     */
    @ApiModelProperty(value = "开始日期（报名时间）", example = "2026-03-01")
    private String startDate;
    
    /**
     * 结束日期（报名时间）
     */
    @ApiModelProperty(value = "结束日期（报名时间）", example = "2026-03-31")
    private String endDate;
}
