package com.zeroone.star.project.dto.j8.sysmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import javax.validation.constraints.NotBlank;
import java.io.Serializable;

@Data
@ApiModel(value = "NoticeDTO", description = "公告保存/修改DTO")
public class NoticeDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "主键ID（修改时必填）", example = "1")
    private Long id;

    @NotBlank(message = "标题不能为空")
    @ApiModelProperty(value = "标题", example = "hellow", required = true)
    private String title;

    @NotBlank(message = "内容不能为空")
    @ApiModelProperty(value = "内容（支持HTML）", example = "<p>hi</p>", required = true)
    private String content;
}