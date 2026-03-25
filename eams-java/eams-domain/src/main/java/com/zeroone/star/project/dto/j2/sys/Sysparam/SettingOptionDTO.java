package com.zeroone.star.project.dto.j2.sys.Sysparam;

import com.fasterxml.jackson.annotation.JsonInclude;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@JsonInclude(JsonInclude.Include.ALWAYS)
public class SettingOptionDTO {
    @ApiModelProperty(value = "主键", example = "1")
    private Long id;

    @ApiModelProperty(value = "组id", example = "1")
    private Long settingId;

    @ApiModelProperty(value = "名称", example = "系统设置")
    private String name;

    @ApiModelProperty(value = "码", example = "normal_setting")
    private String code;

    @ApiModelProperty(value = "值", example = "10")
    private String value;

    @ApiModelProperty(value = "值数据类型", example = "str")
    private String valueType;

    @ApiModelProperty(value = "说明", example = "这是一个系统配置项")
    private String info;

    @ApiModelProperty(value = "排序", example = "0")
    private Integer sortNum;
}
