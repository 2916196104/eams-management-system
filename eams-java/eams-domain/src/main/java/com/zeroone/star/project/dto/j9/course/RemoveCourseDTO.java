package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.List;

/**
 * 移除课程数据传输对象
 * @author yangxiao
 */
@Data
@ApiModel("移除课程数据传输对象")
public class RemoveCourseDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "课程ID列表", required = true)
    private List<Long> ids;
}
