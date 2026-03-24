package com.zeroone.star.student.entity;

import java.io.Serializable;
import java.time.LocalDateTime;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 家长端用户表
 * </p>
 *
 *
 */
@Getter
@Setter
@TableName("user")
public class User implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(type = IdType.AUTO)
    private Long id;

    private String name;

    private Integer wxAccessId;

    private String mobile;

    private String email;

    private Integer state;

    private String password;

    private Integer loginTimes;

    private LocalDateTime latestLoginTime;

    private String latestLoginIp;

    private LocalDateTime addTime;

    private String remark;

    private Long creator;

    private Long schoolId;

    private Long orgId;
}
