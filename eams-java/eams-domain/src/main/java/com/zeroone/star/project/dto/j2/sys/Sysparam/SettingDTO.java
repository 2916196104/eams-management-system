package com.zeroone.star.project.dto.j2.sys.Sysparam;

import com.fasterxml.jackson.annotation.JsonInclude;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@JsonInclude(JsonInclude.Include.ALWAYS)
public class SettingDTO {
    @ApiModelProperty(value = "主键",example = "1")
    private Long id;
    @ApiModelProperty(value = "组名",example = "系统设置")
    private String name;
    @ApiModelProperty(value = "编码",example = "normal_setting")
    private String code;
    @ApiModelProperty(value = "信息",example = "null")
    private String remark;
    @ApiModelProperty(value = "排序",example = "0")
    private Integer sortNum;
}
