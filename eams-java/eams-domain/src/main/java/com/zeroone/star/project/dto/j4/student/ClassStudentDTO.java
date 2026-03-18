package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 描述：班级学员关系操作DTO (加入班级)
 * 对应原型图：【给班级添加学员】弹窗
 */
@Data
public class ClassStudentDTO {

    @ApiModelProperty(value = "班级 ID (必选)", required = true, example = "2008418408985583620")
    private Long classId;

    @ApiModelProperty(value = "学生 ID", notes = "通常从当前登录用户上下文自动获取，若为管理员代操作则需传入", example = "2008418408985583617", required = false)
    private Long studentId;
}