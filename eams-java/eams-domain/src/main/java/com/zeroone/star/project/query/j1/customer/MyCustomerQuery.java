package com.zeroone.star.project.query.j1.customer;

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
 * 描述：我的客户查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("我的客户查询对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
public class MyCustomerQuery extends PageQuery {
    
    /**
     * 客户姓名（模糊查询）
     */
    @ApiModelProperty(value = "客户姓名（模糊查询）", example = "李")
    private String customerName;
    
    /**
     * 客户手机号
     */
    @ApiModelProperty(value = "客户手机号", example = "13800138000")
    private String customerPhone;
    
    /**
     * 客户性别：0-未知 1-男 2-女
     */
    @ApiModelProperty(value = "客户性别：0-未知 1-男 2-女", example = "1")
    private Integer gender;
    
    /**
     * 学历：1-高中及以下 2-大专 3-本科 4-硕士及以上
     */
    @ApiModelProperty(value = "学历：1-高中及以下 2-大专 3-本科 4-硕士及以上", example = "3")
    private Integer education;
    
    /**
     * 意向课程 ID
     */
    @ApiModelProperty(value = "意向课程 ID", example = "2001")
    private Long intentionCourseId;
    
    /**
     * 意向课程名称（模糊查询）
     */
    @ApiModelProperty(value = "意向课程名称（模糊查询）", example = "Java")
    private String intentionCourseName;
    
    /**
     * 客户来源：1-官网 2-公众号 3-朋友推荐 4-电话咨询 5-校园宣讲 6-其他
     */
    @ApiModelProperty(value = "客户来源：1-官网 2-公众号 3-朋友推荐 4-电话咨询 5-校园宣讲 6-其他", example = "1")
    private Integer sourceChannel;
    
    /**
     * 客户级别：A-高意向 B-中意向 C-低意向 D-无效
     */
    @ApiModelProperty(value = "客户级别：A-高意向 B-中意向 C-低意向 D-无效", example = "A")
    private String customerLevel;
    
    /**
     * 跟进状态：0-未分配 1-待跟进 2-跟进中 3-已报名 4-已流失 5-已冻结
     */
    @ApiModelProperty(value = "跟进状态：0-未分配 1-待跟进 2-跟进中 3-已报名 4-已流失 5-已冻结", example = "2")
    private Integer followStatus;
    
    /**
     * 开始日期（创建时间）
     */
    @ApiModelProperty(value = "开始日期（创建时间）", example = "2026-03-01")
    private String startDate;
    
    /**
     * 结束日期（创建时间）
     */
    @ApiModelProperty(value = "结束日期（创建时间）", example = "2026-03-31")
    private String endDate;
}
