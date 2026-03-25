package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.experimental.Accessors;

import java.io.Serializable;
import java.time.LocalDateTime;

@Data
@EqualsAndHashCode(callSuper = false)
@Accessors(chain = true)
@TableName("sys_log")
@ApiModel(value="系统日志", description="系统日志表")
public class SysLog implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "主键 ID", example = "759832058493829123")
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    @ApiModelProperty(value = "操作人 ID", example = "1001")
    @TableField("operator")
    private Long operator;

    @ApiModelProperty(value = "学生 ID", example = "2023001")
    @TableField("student_id")
    private Long studentId;

    @ApiModelProperty(value = "操作类型", example = "INSERT")
    @TableField("type")
    private String type;

    @ApiModelProperty(value = "操作信息", example = "新增学生成功")
    @TableField("info")
    private String info;

    @ApiModelProperty(value = "路径", example = "/api/student/add")
    @TableField("path")
    private String path;

    @ApiModelProperty(value = "请求地址", example = "http://localhost:8080/api/student/add")
    @TableField("url")
    private String url;

    @ApiModelProperty(value = "请求方法", example = "POST")
    @TableField("method")
    private String method;

    @ApiModelProperty(value = "请求参数", example = "{\"name\":\"张三\",\"age\":18}")
    @TableField("param")
    private String param;

    @ApiModelProperty(value = "IP 地址", example = "192.168.1.100")
    @TableField("ip")
    private String ip;

    @ApiModelProperty(value = "浏览器名称", example = "Chrome")
    @TableField("browser_name")
    private String browserName;

    @ApiModelProperty(value = "浏览器版本", example = "114.0.0.0")
    @TableField("browser_ver")
    private String browserVer;

    @ApiModelProperty(value = "系统名称", example = "Windows 10")
    @TableField("os_name")
    private String osName;

    @ApiModelProperty(value = "日志时间", example = "2023-10-27 10:00:00")
    @TableField("add_time")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "响应时间毫秒", example = "120")
    @TableField("time_cost")
    private Integer timeCost;

    @ApiModelProperty(value = "所属组织 ID", example = "10")
    @TableField("org_id")
    private Long orgId;
}
