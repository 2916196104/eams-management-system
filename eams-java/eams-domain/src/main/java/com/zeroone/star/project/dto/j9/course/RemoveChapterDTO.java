package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：移除章节数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Data
@ApiModel("移除章节数据传输对象")
public class RemoveChapterDTO {
    @ApiModelProperty(value = "章节ID", required = true, example = "1")
    @NotNull(message = "章节ID不能为空")
    private Long id;
}