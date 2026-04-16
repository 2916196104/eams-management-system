package com.zeroone.star.stumanager.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 学员跟进表
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Getter
@Setter
@TableName("contact_record")
public class ContactRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 学生id
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
    private Boolean deleted;

    /**
     * 所属组织ID
     */
    private Long orgId;


}
