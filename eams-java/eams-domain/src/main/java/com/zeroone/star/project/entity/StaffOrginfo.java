package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 员工机构信息表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("staff_orginfo")
public class StaffOrginfo implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 员工 id
     */
    private Long staffId;

    /**
     * 所属机构
     */
    private Long orgId;

    /**
     * 所属集团
     */
    private Long groupId;

    /**
     * 所属公司
     */
    private Long comId;

    /**
     * 所属部门
     */
    private Long dptId;

    /**
     * 所属职位
     */
    private Long positionId;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * id 全路径
     */
    private String idPath;
}
