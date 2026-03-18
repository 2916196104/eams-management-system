package com.zeroone.star.project.vo.j2.sys;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：附件上传响应视图对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author belief
 * @version 1.0.0
 */
@Data
@ApiModel("附件上传响应视图对象")
public class AttachmentUploadVO {
    
    @ApiModelProperty(value = "附件ID", example = "att_001")
    private String id;
    
    @ApiModelProperty(value = "原始文件名", example = "student_report.pdf")
    private String originalFilename;
    
    @ApiModelProperty(value = "文件访问URL", example = "http://192.168.1.100:8080/group1/M00/00/00/wKgBhF...")
    private String fileUrl;
    
    @ApiModelProperty(value = "文件大小（字节）", example = "1048576")
    private Long fileSize;
    
    @ApiModelProperty(value = "文件大小（可读格式）", example = "1 MB")
    private String fileSizeReadable;
    
    @ApiModelProperty(value = "文件类型（MIME类型）", example = "application/pdf")
    private String contentType;
    
    @ApiModelProperty(value = "文件扩展名", example = "pdf")
    private String fileExtension;
    
    @ApiModelProperty(value = "MD5校验值", example = "d41d8cd98f00b204e9800998ecf8427e")
    private String md5Hash;
    
    @ApiModelProperty(value = "FastDFS存储组", example = "group1")
    private String storageGroup;
    
    @ApiModelProperty(value = "FastDFS存储路径", example = "M00/00/00/wKgBhF...")
    private String storagePath;
    
    @ApiModelProperty(value = "上传状态：success-成功，failed-失败", example = "success")
    private String uploadStatus;
    
    @ApiModelProperty(value = "上传消息", example = "文件上传成功")
    private String message;
    
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime createTime;
    
    @ApiModelProperty(value = "下载令牌（用于临时访问）")
    private String accessToken;
}