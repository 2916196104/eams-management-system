package com.zeroone.star.project.entity.j1.orgmanager;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("staff_orginfo")
public class StaffOrgInfo {
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    @TableField("staff_id")
    private Long staffId;

    @TableField("org_id")
    private Long orgId;

    @TableField("group_id")
    private Long groupId;

    @TableField("com_id")
    private Long comId;

    @TableField("dpt_id")
    private Long dptId;

    @TableField("position_id")
    private Long positionId;

    @TableField("deleted")
    private Integer deleted;

    @TableField("add_time")
    private LocalDateTime addTime;

    @TableField("creator")
    private Long creator;

    @TableField("id_path")
    private String idPath;
}
