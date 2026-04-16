package com.zeroone.star.course.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * 学科实体（只读，用于关联查询）
 * @author yangxiao
 */
@Getter
@Setter
@TableName("subject")
public class SubjectDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private String name;

    private String info;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;

    private Integer sortNum;

    private Long orgId;
}
