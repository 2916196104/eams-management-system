package com.zeroone.star.login.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

@Data
@TableName("sys_permission")
public class MenuDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId("id")
    private Integer id;

    private String name;

    @TableField("parent_id")
    private String parentId;

    private String url;

    private String code;

    private String path;

    private Integer enabled;

    @TableField("group_name")
    private String groupName;
}
