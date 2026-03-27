package com.zeroone.star.j1.console.entity;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：请款表实体
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@Data
@TableName("cashout")
public class CashoutDO {

    @TableId
    private Long id;

    private String title;

    private Integer type;

    private BigDecimal amount;

    private String payeeName;

    private String account;

    private String info;

    private Integer verifyState;

    private Long verifyStaff;

    private LocalDateTime verifyTime;

    private String verifyRemark;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;

    private String attachFile;

    private Long orgId;
}
