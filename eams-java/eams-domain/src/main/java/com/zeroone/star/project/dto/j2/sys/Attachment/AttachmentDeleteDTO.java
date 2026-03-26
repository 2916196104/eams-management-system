package com.zeroone.star.project.dto.j2.sys.Attachment;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotEmpty;
import java.util.List;

/**
 * <p>
 * 描述：附件删除参数
 * </p>
 * @author 大鹏
 * @version 1.0.0
 */
@Data
@ApiModel("附件删除参数")
public class AttachmentDeleteDTO {

    @ApiModelProperty(value = "附件ID列表", example = "[1, 2]", required = true)
    @NotEmpty(message = "附件ID列表不能为空")
    private List<Long> ids;

    @ApiModelProperty(value = "删除原因", example = "资料已过时")
    private String deleteReason;
}
