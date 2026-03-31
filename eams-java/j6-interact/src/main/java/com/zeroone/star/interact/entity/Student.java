package com.zeroone.star.interact.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Data;

/**
 * <p>
 * 描述:  用来查找学生id，分析excel表中学生是否存在
 * </p>
 *
 * @author upup
 * @version 1.0.0
 * @since 2026-03-30
 */
@Data
public class Student {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;
    /**
     * 姓名
     */
    private String name;
}
