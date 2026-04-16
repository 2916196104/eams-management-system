package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDateTime;

/**
 * 机构/学校表实体（对应org表）
 */
@Getter
@Setter
@TableName("org")
public class OrgDO {

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 上级公司ID
     */
    private Long pid;

    /**
     * 机构名称（学校名称）
     */
    private String name;

    /**
     * 是否有效（1-有效，0-无效）
     */
    private Integer state;

    /**
     * 公司简称
     */
    private String shortname;

    /**
     * 类型
     */
    private Integer type;

    /**
     * 级别 1-集团总部 2-分校(学校) 3-部门
     */
    private Integer level;

    /**
     * ID路径
     */
    private String idPath;

    /**
     * 机构名路径
     */
    private String namePath;

    /**
     * 联系人
     */
    private String contactName;

    /**
     * 联系电话
     */
    private String phone;

    /**
     * 传真
     */
    private String fax;

    /**
     * 邮箱
     */
    private String email;

    /**
     * 描述
     */
    private String info;

    /**
     * 创建人ID
     */
    private Long creator;

    /**
     * 编辑人ID
     */
    private Long editor;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记（0-未删，1-已删）
     */
    @TableLogic
    private Integer deleted;

    /**
     * 省
     */
    private Integer province;

    /**
     * 市
     */
    private Integer city;

    /**
     * 区
     */
    private Integer district;

    /**
     * 地址
     */
    private String address;

    /**
     * 排序
     */
    private Integer sortNum;

    /**
     * 营业执照
     */
    private String license;
}