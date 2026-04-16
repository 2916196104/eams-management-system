package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 学员跟进表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("contact_record")
public class ContactRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 学生 id
     */
    private Long studentId;

    /**
     * 跟进记录
     */
    private String info;

    /**
     * 联系时间
     */
    private LocalDateTime contactTime;

    /**
     * 下次联系时间
     */
    private LocalDateTime contactNextTime;

    /**
     * 联系方式
     */
    private Integer contactType;

    /**
     * 联系电话
     */
    private String contactPhone;

    /**
     * 创建者
     */
    private Long creator;

    /**
     * 时间
     */
    private LocalDateTime addTime;

    /**
     * 进展阶段
     */
    private Integer stage;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 所属组织 ID
     */
    private Long orgId;
}
