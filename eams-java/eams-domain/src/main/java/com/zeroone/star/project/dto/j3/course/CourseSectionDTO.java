package com.zeroone.star.project.dto.j3.course;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：课程章节数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author j3组 殇昌
 * @version 1.0.0
 */
@Data
public class CourseSectionDTO {

    @ApiModelProperty(value = "章节id", example = "1")
    private Long id;

    @ApiModelProperty(value = "所属课程id", example = "1001", required = true)
    private Long courseId;

    @ApiModelProperty(value = "章节标题", example = "素描", required = true)
    private String title;

    @ApiModelProperty(value = "计划课时数", example = "3", required = true)
    private Integer lessonCount;
}