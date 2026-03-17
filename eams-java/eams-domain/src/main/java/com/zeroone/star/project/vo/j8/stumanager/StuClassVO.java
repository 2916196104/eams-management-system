package com.zeroone.star.project.vo.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@ApiModel("学员班级列表")
@Data
public class StuClassVO {
    @ApiModelProperty(value = "序号", example = "2")
    private Long classId;
    @ApiModelProperty(value = "班级名称", example = "2班")
    private String className;
    @ApiModelProperty(value = "科目名称", example = "英语")
    private String subjectName;
    @ApiModelProperty(value = "教室名称", example = "xxx")
    private String classroomName;
    @ApiModelProperty(value = "学生人数", example = "2")
    private Integer studentNum;
    @ApiModelProperty(value = "最大学生人数", example = "50")
    private Integer overStudentName;
}
