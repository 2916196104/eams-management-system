package com.zeroone.star.sys.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 员工机构信息表
 * </p>
 *
 * @author isme
 * @since 2026-03-22
 */
@Getter
@Setter
@TableName("staff_orginfo")
public class StaffOrginfo implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 员工id
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
    private Boolean deleted;

    private LocalDateTime addTime;

    private Long creator;

    /**
     * id全路径
     */
    private String idPath;


}
