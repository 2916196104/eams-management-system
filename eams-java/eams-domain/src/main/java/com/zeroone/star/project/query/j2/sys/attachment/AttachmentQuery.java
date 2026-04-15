package com.zeroone.star.project.query.j2.sys.attachment;

import com.zeroone.star.project.dto.PageDTO;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：附件查询条件对象
 * </p>
 * @author belief
 * @version 1.0.0
 */
@Data
@ApiModel("附件查询条件对象")
public class AttachmentQuery extends PageDTO {
    
    @ApiModelProperty(value = "附件类型", example = "pdf")
    private String fileType;
    
    @ApiModelProperty(value = "附件名称（模糊查询）", example = "成绩单")
    private String name;
    
    @ApiModelProperty(value = "文件原名（模糊查询）", example = "report")
    private String fileName;
    
    @ApiModelProperty(value = "创建人ID", example = "1")
    private Integer creator;
    
    @ApiModelProperty(value = "添加时间开始")
    private LocalDateTime addTimeStart;
    
    @ApiModelProperty(value = "添加时间结束")
    private LocalDateTime addTimeEnd;
    
    @ApiModelProperty(value = "排序字段：add_time, file_size", example = "add_time")
    private String orderBy = "add_time";
    
    @ApiModelProperty(value = "排序方向：asc, desc", example = "desc")
    private String orderDirection = "desc";
}