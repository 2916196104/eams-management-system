package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 物料出入库记录
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("material_record")
public class MaterialRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 物料 ID
     */
    private Long materialId;

    /**
     * 变动数量
     */
    private Integer amount;

    /**
     * 变动原因说明
     */
    private String reason;

    /**
     * 变动类型 1 入库 2 出库 3 积分商城出库
     */
    private Integer changeType;

    /**
     * 变动对象 id 如积分商城里的商品 id
     */
    private Long changeTargetId;

    /**
     * 备注信息
     */
    private String remark;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 变动时间
     */
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 涉及学生 id
     */
    private Long studentId;

    /**
     * 涉及员工 id
     */
    private Long staffId;

    /**
     * 所属物料的组织 ID
     */
    private Long orgId;

    /**
     * 学校 id
     */
    private Long schoolId;
}
