package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：班级学员关系操作DTO (加入/退出)
 */
@Data
public class ClassStudentDTO {

    @ApiModelProperty(value = "班级ID", required = true, example = "2008418408985583620")
    private Long classId;

    @ApiModelProperty(value = "学生ID", required = true, example = "2008418408985583617")
    private Long studentId;

    @ApiModelProperty(value = "加入原因 (1:正常入学 2:转班 3:补录 其他:自定义)", example = "1")
    private Integer reason;

    @ApiModelProperty(value = "备注信息", example = "从Python班转入")
    private String remark;

    @ApiModelProperty(value = "默认消费课程ID", required = true, example = "1001")
    private Long consumeCourseId;
}