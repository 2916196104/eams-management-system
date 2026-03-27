package com.zeroone.star.j1.console.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.util.Date;

/**
 * <p>
 * 教室表
 * </p>
 * @author hxb
 */
@Getter
@Setter
@TableName("classroom")
public class ClassroomDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 教室名
     */
    private String name;

    /**
     * 位置
     */
    private String address;

    /**
     * 面积平方米
     */
    private Integer area;

    /**
     * 备注
     */
    private String remark;

    /**
     * 创建者
     */
    private Long creator;

    /**
     * 编辑者
     */
    private Long editor;

    /**
     * 创建时间
     */
    private Date addTime;

    /**
     * 编辑时间
     */
    private Date editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 创建者所属学校ID
     */
    private Long schoolId;

    /**
     * 创建者所属组织ID
     */
    private Long orgId;
}
