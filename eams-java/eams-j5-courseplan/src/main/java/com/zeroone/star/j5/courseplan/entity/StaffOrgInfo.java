package com.zeroone.star.j5.courseplan.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 员工/组织架构关联表 实体类
 * </p>
 *
 * @author YourName
 * @since 2026-03-19
 */
@Data
@TableName("staff_orginfo")
public class StaffOrgInfo {
    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 员工id
     */
    @TableField("staff_id")
    private Long staffId;

    /**
     * 所属机构
     */
    @TableField("org_id")
    private Long orgId;

    /**
     * 所属集团
     */
    @TableField("group_id")
    private Long groupId;

    /**
     * 所属公司
     */
    @TableField("com_id")
    private Long comId;

    /**
     * 所属部门
     */
    @TableField("dpt_id")
    private Long dptId;

    /**
     * 所属职位
     */
    @TableField("position_id")
    private Long positionId;

    /**
     * 删除标记 (0:正常, 1:删除)
     */
    @TableField("deleted")
    @TableLogic // 开启逻辑删除
    private Integer deleted;

    /**
     * 添加时间
     */
    @TableField(value = "add_time", fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 创建人ID
     */
    @TableField("creator")
    private Long creator;

    /**
     * id全路径 (例如: 1/10/105)
     */
    @TableField("id_path")
    private String idPath;
}

