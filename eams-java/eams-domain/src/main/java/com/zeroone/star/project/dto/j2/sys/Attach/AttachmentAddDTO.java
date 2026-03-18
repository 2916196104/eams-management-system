package com.zeroone.star.project.dto.j2.sys.Attach;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

/**
 * <p>
 * 描述：附件上传数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author belief
 * @version 1.0.0
 */
@Data
@ApiModel("附件上传数据传输对象")
public class AttachmentAddDTO {
    
    @ApiModelProperty(value = "上传的文件", required = true)
    @NotNull(message = "上传文件不能为空")
    private MultipartFile file;
    
    @ApiModelProperty(value = "业务模块", required = true, example = "student_management")
    @NotBlank(message = "业务模块不能为空")
    @Size(max = 50, message = "业务模块长度不能超过50个字符")
    private String businessModule;
    
    @ApiModelProperty(value = "业务ID", required = true, example = "student_2024001")
    @NotBlank(message = "业务ID不能为空")
    @Size(max = 100, message = "业务ID长度不能超过100个字符")
    private String businessId;
    
    @ApiModelProperty(value = "附件类型", example = "document")
    @Size(max = 20, message = "附件类型长度不能超过20个字符")
    private String attachmentType;
    
    @ApiModelProperty(value = "附件名称", example = "学生成绩单")
    @Size(max = 200, message = "附件名称长度不能超过200个字符")
    private String attachmentName;
    
    @ApiModelProperty(value = "附件描述", example = "2024年第一学期期末考试成绩单")
    @Size(max = 500, message = "附件描述长度不能超过500个字符")
    private String description;
    
    @ApiModelProperty(value = "是否公开：0-私有，1-公开", example = "0")
    private Integer isPublic = 0;
    
    @ApiModelProperty(value = "上传者ID", example = "user_001")
    @Size(max = 50, message = "上传者ID长度不能超过50个字符")
    private String uploaderId;
    
    @ApiModelProperty(value = "上传者姓名", example = "张三")
    @Size(max = 50, message = "上传者姓名长度不能超过50个字符")
    private String uploaderName;
}