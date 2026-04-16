package com.zeroone.star.project.vo.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(value = "StudentAvatarVO", description = "学员头像数据传输对象")
public class StudentHeadImgVO {

    @ApiModelProperty(value = "学员ID", example = "10001")
    private Long id;

    @ApiModelProperty(value = "头像地址", example = "https://xxx.com/headImg.jpg")
    private String headImg;
}