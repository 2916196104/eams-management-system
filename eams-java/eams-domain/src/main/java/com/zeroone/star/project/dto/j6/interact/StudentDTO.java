package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述:
 * </p>
 *
 * @author upup
 * @version 1.0.0
 * @since 2026-03-30
 */
@Data
@ApiModel("学生数据对象")
public class StudentDTO {
    /**
     * 主键ID
     */
    @ApiModelProperty(value = "成绩id,用来查找学生id",example = "2030583010845589505")
    private Long id;
    /**
     * 姓名
     */
    @ApiModelProperty(value = "学生姓名",example = "王五")
    private String name;
}
