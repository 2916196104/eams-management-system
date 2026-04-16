package com.zeroone.star.project.vo.j8.SaveStu;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 通用字典下拉选项VO
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("通用字典下拉选项")
public class DictVO {

    @ApiModelProperty(value = "选项编码（后端存储用）", example = "1")
    private Integer value;

    @ApiModelProperty(value = "选项显示文本（前端展示用）", example = "爸爸")
    private String label;
}
