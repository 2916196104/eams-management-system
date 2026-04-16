package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.util.List;

/**
 * 移除关联课程数据
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("移除关联课程数据")
public class CourseLinkRemoveDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "课程ID", required = true, example = "100")
    private Long courseId;

    @ApiModelProperty(value = "要移除的关联课程ID列表", required = true)
    private List<Long> linkedIds;
}
