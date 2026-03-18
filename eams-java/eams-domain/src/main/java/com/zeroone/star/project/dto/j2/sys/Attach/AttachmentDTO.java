package com.zeroone.star.project.dto.j2.sys.Attach;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：附件数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author belief
 * @version 1.0.0
 */
@Data
@ApiModel("附件数据传输对象")
public class AttachmentDTO {
    
    @ApiModelProperty(value = "附件ID", example = "att_001")
    private String id;
    
    @ApiModelProperty(value = "原始文件名", example = "student_report.pdf")
    private String originalFilename;
    
    @ApiModelProperty(value = "存储文件名", example = "20240318_123456.pdf")
    private String storedFilename;
    
    @ApiModelProperty(value = "文件路径（FastDFS路径）", example = "group1/M00/00/00/wKgBhF...")
    private String filePath;
    
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
    
    @ApiModelProperty(value = "业务模块", example = "student_management")
    private String businessModule;
    
    @ApiModelProperty(value = "业务ID", example = "student_2024001")
    private String businessId;
    
    @ApiModelProperty(value = "附件类型", example = "document")
    private String attachmentType;
    
    @ApiModelProperty(value = "附件名称", example = "学生成绩单")
    private String attachmentName;
    
    @ApiModelProperty(value = "附件描述", example = "2024年第一学期期末考试成绩单")
    private String description;
    
    @ApiModelProperty(value = "是否公开：0-私有，1-公开", example = "0")
    private Integer isPublic;
    
    @ApiModelProperty(value = "上传者ID", example = "user_001")
    private String uploaderId;
    
    @ApiModelProperty(value = "上传者姓名", example = "张三")
    private String uploaderName;
    
    @ApiModelProperty(value = "下载次数", example = "5")
    private Integer downloadCount = 0;
    
    @ApiModelProperty(value = "状态：0-正常，1-已删除", example = "0")
    private Integer status = 0;
    
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime createTime;
    
    @ApiModelProperty(value = "更新时间")
    private LocalDateTime updateTime;
}