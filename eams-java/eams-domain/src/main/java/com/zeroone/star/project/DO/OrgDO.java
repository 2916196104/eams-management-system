package com.zeroone.star.project.DO;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * 机构表DO实体
 */
@Data
@TableName("org")
public class OrgDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 上级公司ID
     */
    private Long pid;

    /**
     * 公司名称
     */
    private String name;

    /**
     * 是否有效 0-禁用 1-启用
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
     * 级别 1-集团总部 2-分校 3-部门
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
     * Email
     */
    private String email;

    /**
     * 描述
     */
    private String info;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 添加时间
     */
    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField(fill = FieldFill.INSERT_UPDATE)
    private LocalDateTime editTime;

    /**
     * 删除标记 0-未删除 1-已删除
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
