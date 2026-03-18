package com.zeroone.star.project.query.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：附件查询条件对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author belief
 * @version 1.0.0
 */
@Data
@ApiModel("附件查询条件对象")
public class AttachmentQuery extends PageDTO {
    
    @ApiModelProperty(value = "业务模块", example = "student_management")
    private String businessModule;
    
    @ApiModelProperty(value = "业务ID", example = "student_2024001")
    private String businessId;
    
    @ApiModelProperty(value = "附件类型", example = "document")
    private String attachmentType;
    
    @ApiModelProperty(value = "附件名称（模糊查询）", example = "成绩单")
    private String attachmentName;
    
    @ApiModelProperty(value = "原始文件名（模糊查询）", example = "report")
    private String originalFilename;
    
    @ApiModelProperty(value = "文件类型", example = "application/pdf")
    private String contentType;
    
    @ApiModelProperty(value = "是否公开：0-私有，1-公开", example = "0")
    private Integer isPublic;
    
    @ApiModelProperty(value = "上传者ID", example = "user_001")
    private String uploaderId;
    
    @ApiModelProperty(value = "状态：0-正常，1-已删除", example = "0")
    private Integer status = 0;
    
    @ApiModelProperty(value = "创建时间开始")
    private LocalDateTime createTimeStart;
    
    @ApiModelProperty(value = "创建时间结束")
    private LocalDateTime createTimeEnd;
    
    @ApiModelProperty(value = "排序字段：create_time, file_size, download_count", example = "create_time")
    private String orderBy = "create_time";
    
    @ApiModelProperty(value = "排序方向：asc, desc", example = "desc")
    private String orderDirection = "desc";
}