package com.zeroone.star.eamsj3data.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 学员跟进记录实体
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
@Getter
@Setter
@TableName("contact_record")
public class ContactRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 学员ID
     */
    private Long studentId;

    /**
     * 进展阶段
     */
    private Integer stage;

    /**
     * 创建时间
     */
    private LocalDateTime addTime;

    /**
     * 删除标记
     */
    private Integer deleted;
}
