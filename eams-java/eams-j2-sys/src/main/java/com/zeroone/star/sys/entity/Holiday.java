package com.zeroone.star.sys.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 节假日设置
 * </p>
 *
 * @author Wind
 * @since 2026-03-23
 */
@Getter
@Setter
public class Holiday implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    private LocalDate date;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;


}
