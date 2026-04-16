package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.List;

/**
 * 移除关联课程数据传输对象
 * @author yangxiao
 */
@Data
@ApiModel("移除关联课程数据传输对象")
public class RemoveRelatedCourseDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "课程ID", required = true, example = "100")
    private Long courseId;

    @ApiModelProperty(value = "要移除的关联课程ID列表", required = true)
    private List<Long> linkedIds;
}

