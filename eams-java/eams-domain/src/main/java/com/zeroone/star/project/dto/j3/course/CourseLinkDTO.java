package com.zeroone.star.project.dto.j3.course;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：关联课程传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author j3组 KINGHOG
 * @version 1.0.0
 */
@Data
public class CourseLinkDTO {
    @ApiModelProperty(value = "主键", example = "2", required = true)
    private Long id;
    @ApiModelProperty(value = "课程id", example = "4", required = true)
    private Long courseId;
    @ApiModelProperty(value = "关联课程id", example = "2", required = true)
    private Long linkedId;


}
