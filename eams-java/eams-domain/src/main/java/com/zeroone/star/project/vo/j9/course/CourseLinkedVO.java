package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;

/**
 * 关联课程展示对象
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("关联课程")
public class CourseLinkedVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "关联课程ID", example = "2")
    private Long id;

    @ApiModelProperty(value = "关联课程名称", example = "Java进阶实战课")
    private String name;

    @ApiModelProperty(value = "关联课程封面", example = "/images/course/java-adv.png")
    private String cover;
}
