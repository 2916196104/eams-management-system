package com.zeroone.star.project.vo.j5.courseplan;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：教师/助教通用选项对象
 * </p>
 *
 * @author taohu5564
 * @since 2023/5/17 14:04
 */
@Data
public class TeacherOptionVO {
    @ApiModelProperty(value = "人员ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "人员名称", example = "张三")
    private String name;

    @ApiModelProperty(value = "职位名称", example = "讲师")
    private String positionName;

    @ApiModelProperty(value = "人员类型 1:上课老师, 2:助教", example = "1")
    private Integer typeNum;

}
