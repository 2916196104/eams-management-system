package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

@Data
@ApiModel(value = "StudentHeadImgDTO", description = "学员头像数据传输对象")
public class StudentHeadImgDTO {

    @NotNull(message = "学生ID不能为空")
    @ApiModelProperty(value = "学员ID", example = "10001")
    private Long id;

    @NotBlank(message = "头像地址不能为空")
    @ApiModelProperty(value = "头像地址", example = "https://xxx.com/headImg.jpg")
    private String headImg;
}