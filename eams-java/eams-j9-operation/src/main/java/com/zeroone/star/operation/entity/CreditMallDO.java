package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * 积分商城礼品实体
 */
@Getter
@Setter
@TableName("credit_mall")
public class CreditMallDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long schoolId;

    private Long materialId;

    private Long categoryId;

    private String categoryName;

    private String name;

    private Integer credit;

    private Integer state;

    private Integer saleNum;

    private Integer viewNum;

    private String cover;

    private String content;
    @TableField(fill = FieldFill.INSERT)
    private Long creator;
    @TableField(fill = FieldFill.UPDATE)
    private Long editor;
     @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;
     @TableField(fill = FieldFill.UPDATE)
    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;

    private Long orgId;
}
