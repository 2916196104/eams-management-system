package com.zeroone.star.project.dto.j2.sys.Attachment;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

/**
 * <p>
 * 描述：附件修改参数
 * </p>
 * @author 大鹏
 * @version 1.0.0
 */
@Data
@ApiModel("附件修改参数")
public class AttachmentUpdateDTO {

    /**
     * 附件ID
     */
    @NotNull(message = "附件ID不能为空")
    private Long id;

    /**
     * 附件名称（用户自定义名称，用于显示）
     * 可选，不传则不修改
     */
    private String name;

    /**
     * 文件原名（原始文件名）
     * 可选，不传则不修改
     */
    private String fileName;

    //其他字段一律是上传时候生成的不能修改；


}
