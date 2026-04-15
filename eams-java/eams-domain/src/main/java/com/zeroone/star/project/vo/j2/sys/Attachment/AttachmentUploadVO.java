package com.zeroone.star.project.vo.j2.sys.Attachment;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：附件上传响应视图对象
 * </p>
 * @author belief
 * @version 1.0.0
 */
@Data
@ApiModel("附件上传响应视图对象")
public class AttachmentUploadVO {

    @ApiModelProperty(value = "附件ID", example = "1")
    private Integer  id;

    @ApiModelProperty(value = "文件原名", example = "student_report.pdf")
    private String fileName;

    @ApiModelProperty(value = "附件大小（字节）", example = "1048576")
    private Integer  fileSize;

    @ApiModelProperty(value = "文件大小（可读格式）", example = "1 MB")
    private String fileSizeReadable;

    @ApiModelProperty(value = "附件类型", example = "pdf")
    private String fileType;

    @ApiModelProperty(value = "附件名称", example = "学生成绩单")
    private String name;

    @ApiModelProperty(value = "附件地址", example = "/uploads/2024/03/22/abc.pdf")
    private String url;

    @ApiModelProperty(value = "保存路径", example = "/uploads/2024/03/22/")
    private String savePath;

    @ApiModelProperty(value = "添加时间")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "创建人ID", example = "1")
    private Integer creator;

    @ApiModelProperty(value = "上传状态：success-成功，failed-失败", example = "success")
    private String uploadStatus;

    @ApiModelProperty(value = "上传消息", example = "文件上传成功")
    private String message;
}
