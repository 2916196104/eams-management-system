package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 审核操作记录
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("operation_record")
public class OperationRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 类型
     */
    private Integer type;

    /**
     * 审核对象
     */
    private Long itemId;

    /**
     * 审核状态
     */
    private String state;

    /**
     * 审核备注
     */
    private String content;

    /**
     * 审核人
     */
    private Long creator;

    /**
     * 处理时间
     */
    private LocalDateTime addTime;

    /**
     * 所属组织 ID
     */
    private Long orgId;
}
