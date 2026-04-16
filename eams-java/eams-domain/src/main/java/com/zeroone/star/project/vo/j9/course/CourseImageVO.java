package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;

/**
 * 课程图片展示对象
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("课程图片")
public class CourseImageVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "图片ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "图片地址", example = "/images/course/detail01.png")
    private String imageUrl;
}
