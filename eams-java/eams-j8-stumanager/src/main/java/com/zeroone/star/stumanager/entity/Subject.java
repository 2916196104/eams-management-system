package com.zeroone.star.stumanager.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * 科目表
 */
@Getter
@Setter
@TableName("subject")
public class Subject implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 科目名称
     */
    private String name;

    /**
     * 简介
     */
    private String info;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑者
     */
    private Long editor;

    /**
     * 新增时间
     */
    private LocalDateTime addTime;

    /**
     * 修改时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Boolean deleted;

    /**
     * 排序值
     */
    private Integer sortNum;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;

}
