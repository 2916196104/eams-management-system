package com.zeroone.star.sys.entity;

import com.baomidou.mybatisplus.annotation.*;

import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 系统用户日志
 * </p>
 *
 * @author isme
 * @since 2026-03-15
 */
@Getter
@Setter
@TableName("sys_log")
public class SysLog implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 操作人
     */
    private Long operator;

    /**
     * 学生id
     */
    private Integer studentId;

    /**
     * 类型
     */
    private String type;

    /**
     * 信息
     */
    private String info;

    /**
     * 路径
     */
    private String path;

    /**
     * 请求地址
     */
    private String url;

    /**
     * 请求方法
     */
    private String method;

    /**
     * 参数
     */
    private String param;

    /**
     * IP地址
     */
    private String ip;

    /**
     * 浏览器名
     */
    private String browserName;

    /**
     * 浏览器版本
     */
    private String browserVer;

    /**
     * 系统名称
     */
    private String osName;


    /**
     * 日志时间
     */
    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 响应时间毫秒
     */
    private Integer timeCost;

    /**
     * 所属组织ID
     */
    private Long orgId;


}
