package com.zeroone.star.login.entity;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

@Data
@TableName("sys_role")
public class RoleDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId("id")
    private Integer id;

    private String name;

    private String code;
}
