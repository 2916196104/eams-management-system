package com.zeroone.star.project.dto.j2.sys.Template;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalDateTime;

/**
 * 模板传输对象
 */
@Data
@ApiModel("模板文件传输数据对象")
public class TemplateAttachmentDTO {
    @ApiModelProperty(value = "编号", example = "123456")
    @NotNull(message = "编号不能为空")
    @Min(value = 1, message = "编号不能为非正数")
    private Long id;

    @ApiModelProperty(value = "文件原名", example = "学员模板.xlsx")
    @NotBlank(message = "文件原名不能为空")
    private String fileName;

    @ApiModelProperty(value = "附件大小", example = "12")
    @NotNull(message = "附件大小不能为空")
    @Min(value = 0, message = "文件大小不能为负数")
    private Integer fileSize;

    @ApiModelProperty(value = "附件类型", example = "模板")
    @NotBlank(message = "附件类型不能为空")
    private String fileType;

    @ApiModelProperty(value = "附件名称", example = "学员模板")
    @NotBlank(message = "附件名称不能为空")
    private String name;

    @ApiModelProperty(value = "附件地址", example = "http://192.168.188.128:8888/group1/M00/00/00/oYYBAGnFlbmADxUlAABO1748Kvs68.xlsx")
    @NotBlank(message = "附件地址不能为空")
    private String url;

    @ApiModelProperty(value = "保存路径", example = "C:\\Users\\15645\\Desktop")
    private String savePath;

    @ApiModelProperty(value = "添加时间", example = "2026-03-27 07:08:09")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "创建时间", example = "123456")
    private Long creator;
}
