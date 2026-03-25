package com.zeroone.star.login.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;

/**
 * Menu resource loaded from permission data.
 */
@Getter
@Setter
public class Menu implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    private String name;

    private String linkUrl;

    /**
     * Frontend route path, or falls back to the permission code.
     */
    private String path;

    private Integer priority;

    private String icon;

    private String code;

    private String description;

    private Integer parentMenuId;

    private Integer level;

    private Integer isEnable;

    private String groupName;
}
