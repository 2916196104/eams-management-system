package com.zeroone.star.project.dto.j9.course;
import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalDateTime;

/**
 * 课程图片DTO
 */
@Data
@ApiModel(description = "课程图片DTO")
public class CourseImageDTO {


    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;


    @ApiModelProperty(value = "所属课程ID", example = "101", required = true)
    private Long courseId;

    @NotBlank(message = "图片地址不能为空")
    @ApiModelProperty(value = "图片地址", example = "https://example.com/image.jpg", required = true)
    private String imageUrl;

    @ApiModelProperty(value = "创建人ID", example = "1001")
    private Long creator;

    @ApiModelProperty(value = "编辑人ID", example = "1002")
    private Long editor;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "添加时间", example = "2024-01-15 10:30:00")
    private LocalDateTime addTime;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "编辑时间", example = "2024-01-20 14:30:00")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "删除标记: 0-未删除, 1-已删除", example = "0")
    private Integer deleted = 0;
}
