package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("subject")
public class SubjectDO {
    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;
    /**
     * 科目
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
     * 创建者所属组织ID
     */
    private Long orgId;
}
