package com.zeroone.star.material.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 物料出入库记录
 * </p>
 *
 * @author fantast
 * @since 2026-03-16
 */
@Getter
@Setter
@TableName("material_record")
public class MaterialRecordDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 物料ID
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
     * 变动类型1入库2出库3积分商城出库
     */
    private Integer changeType;

    /**
     * 变动对象id如积分商城里的商品id
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
    @TableLogic
    private Boolean deleted;

    /**
     * 涉及学生id
     */
    private Long studentId;

    /**
     * 涉及员工id
     */
    private Long staffId;

    /**
     * 所属物料的组织ID
     */
    private Long orgId;

    /**
     * 学校id
     */
    private Long schoolId;
}
