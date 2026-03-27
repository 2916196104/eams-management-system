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
 * 学员跟进表
 * </p>
 * @author hxb
 */
@Getter
@Setter
@TableName("contact_record")
public class ContactRecordDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 学生id
     */
    private Long studentId;

    /**
     * 跟进记录
     */
    private String info;

    /**
     * 联系时间
     */
    private Date contactTime;

    /**
     * 下次联系时间
     */
    private Date contactNextTime;

    /**
     * 联系方式
     */
    private Integer contactType;

    /**
     * 联系电话
     */
    private String contactPhone;

    /**
     * 创建者
     */
    private Long creator;

    /**
     * 时间
     */
    private Date addTime;

    /**
     * 进展阶段
     */
    private Integer stage;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 所属组织ID
     */
    private Long orgId;
}
