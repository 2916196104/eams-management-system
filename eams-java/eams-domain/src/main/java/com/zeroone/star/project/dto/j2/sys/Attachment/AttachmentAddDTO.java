package com.zeroone.star.project.dto.j2.sys.Attachment;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

/**
 * <p>
 * 描述：附件上传数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author belief
 * @version 1.0.0
 */
@Data
@ApiModel(value = "附件上传数据传输对象", description = "用于接收前端上传的附件信息")
public class AttachmentAddDTO {

    @ApiModelProperty(value = "上传的文件", required = true, dataType = "__file")
    @NotNull(message = "上传文件不能为空")
    private MultipartFile file;

    @ApiModelProperty(value = "附件名称", example = "学生成绩单", notes = "附件显示名称，最大100字符")
    @Size(max = 100, message = "附件名称长度不能超过100个字符")
    private String name;

    @ApiModelProperty(value = "创建人ID", example = "1", notes = "创建人ID（超级管理员身份id为1则传入1）")
    @NotNull(message = "创建人ID不能为空")
    private Integer creator;
}
