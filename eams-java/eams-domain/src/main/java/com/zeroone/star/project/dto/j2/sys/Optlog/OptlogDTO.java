package com.zeroone.star.project.dto.j2.sys.Optlog;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description  操作日志数据传输对象
 * @title com.zeroone.star.project.dto.j2.sys
 * @date 2026/3/15
 */
@Data
public class OptlogDTO {
    @ApiModelProperty(value = "日志时间",example = "2026-03-15 13:00")
    private String add_time;
    @ApiModelProperty(value = "操作人",example = "管理员")
    private String operator;
    @ApiModelProperty(value = "操作类型",example = "老师登录")
    private String type;
    @ApiModelProperty(value = "操作内容",example = "登录成功")
    private String info;
    @ApiModelProperty(value = "请求路径",example = "/app/common/login")
    private String org_id;
    @ApiModelProperty(value = "系统",example = "Windows 10")
    private String os_name;
    @ApiModelProperty(value = "IP地址",example = "127.0.0.1")
    private String browser_ver;
    @ApiModelProperty(value = "浏览器",example = "Chrome 14")
    private String broswer_name;
    @ApiModelProperty(value = "响应时间",example = "102")
    private String time_cost;
}
