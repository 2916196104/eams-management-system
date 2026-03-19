// src/main/java/com/zeroone/star/project/dto/j2/sys/AttachmentUpdateDTO.java
package com.zeroone.star.project.dto.j2.sys.Attach;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
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

    @ApiModelProperty(value = "附件ID", example = "att_001", required = true)
    @NotBlank(message = "附件ID不能为空")
    private String id;

    @ApiModelProperty(value = "附件名称", example = "学生成绩单")
    @Size(max = 100, message = "附件名称不能超过100个字符")
    private String attachmentName;

    @ApiModelProperty(value = "附件描述", example = "2024年第一学期期末考试成绩单")
    @Size(max = 500, message = "附件描述不能超过500个字符")
    private String description;

    @ApiModelProperty(value = "附件类型", example = "document")
    private String attachmentType;

    @ApiModelProperty(value = "是否公开：0-私有，1-公开", example = "0")
    private Integer isPublic;

    @ApiModelProperty(value = "业务模块", example = "student_management")
    private String businessModule;

    @ApiModelProperty(value = "业务ID", example = "student_2024001")
    private String businessId;

    @ApiModelProperty(value = "修改原因", example = "更正文件名错误")
    private String updateReason;
}
