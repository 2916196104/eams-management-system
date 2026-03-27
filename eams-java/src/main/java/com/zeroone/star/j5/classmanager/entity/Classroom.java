package com.zeroone.star.j5.classmanager.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

/**
 * <p>
 * 教室
 * </p>
 *
 * @author j5-luohan
 * @since 2026-03-23
 */
@Getter
@Setter
@Accessors(chain = true)
@TableName("classroom")
public class Classroom implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId("id")
    private Long id;

    /**
     * 教室名
     */
    @TableField("name")
    private String name;

    /**
     * 位置
     */
    @TableField("address")
    private String address;

    /**
     * 面积平方米
     */
    @TableField("area")
    private Integer area;

    /**
     * 备注
     */
    @TableField("remark")
    private String remark;

    /**
     * 创建者
     */
    @TableField("creator")
    private Long creator;

    /**
     * 编辑者
     */
    @TableField("editor")
    private Long editor;

    /**
     * 创建时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    @TableField("deleted")
    private Boolean deleted;

    /**
     * 创建者所属学校ID
     */
    @TableField("school_id")
    private Long schoolId;

    /**
     * 创建者所属组织ID
     */
    @TableField("org_id")
    private Long orgId;


}
