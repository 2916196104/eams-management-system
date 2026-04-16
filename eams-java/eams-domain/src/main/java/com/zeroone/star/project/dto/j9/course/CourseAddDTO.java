package com.zeroone.star.project.dto.j9.course;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.math.BigDecimal;
import java.util.List;

/**
 * 新增课程参数 DTO
 */
@Data
@ApiModel(description = "新增课程参数")
public class CourseAddDTO {

    @NotBlank(message = "课程名称不能为空")
    @ApiModelProperty(value = "课程名称", required = true, example = "零基础钢琴入门")
    private String name;

    @NotNull(message = "所属机构不能为空")
    @ApiModelProperty(value = "机构ID", required = true, example = "1")
    private Long orgId;

    @NotNull(message = "所属科目不能为空")
    @ApiModelProperty(value = "科目ID", required = true, example = "10")
    private Long subjectId;

    @ApiModelProperty(value = "课程价格", example = "199.00")
    private BigDecimal price;

    @ApiModelProperty(value = "课程状态（0=禁用, 1=启用）", example = "1")
    private Integer state;

    @ApiModelProperty(value = "课程封面图片URL", example = "http://xxx.com/cover.jpg")
    private String cover;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "课程详情图片URL列表", example = "[\"url1.jpg\", \"url2.jpg\"]")
    private List<String> pictures;
}