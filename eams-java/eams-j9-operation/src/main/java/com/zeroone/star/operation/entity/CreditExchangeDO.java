package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * 积分商城兑换记录实体
 */
@Getter
@Setter
@TableName("credit_exchange")
public class CreditExchangeDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long creditMallId;

    private Long schoolId;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;

    private Long studentId;

    private Long userId;

    private Integer num;

    private String credit;

    private Integer verifyState;

    private Long verifyStaff;

    private LocalDateTime verifyTime;

    private String verifyRemark;
}
