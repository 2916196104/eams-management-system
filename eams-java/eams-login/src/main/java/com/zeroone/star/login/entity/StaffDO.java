package com.zeroone.star.login.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

@Data
@TableName("staff")
public class StaffDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId("id")
    private Long id;

    private String name;

    private String mobile;

    @TableField("head_img")
    private String headImg;

    private String password;

    private Byte state;

    private Byte deleted;

    @TableField("org_id")
    private Long orgId;
}
