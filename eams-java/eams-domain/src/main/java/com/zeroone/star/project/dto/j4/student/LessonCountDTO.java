package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;
import java.util.Date;

@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("获取消课记录（条件+分页）")
public class LessonCountDTO {

    @ApiModelProperty(value = "序号", example = "1")
    private String id;
    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String student_name;
    @ApiModelProperty(value = "变动数量", example = "+20")
    private String change_number;
    @ApiModelProperty(value = "剩余数量", example = "35")
    private String remain_number;
    @ApiModelProperty(value = "课程", example = "绘画")
    private String course_name;
    @ApiModelProperty(value = "上课日期", example = "2026-3-15")
    private LocalDateTime course_time;
    @ApiModelProperty(value = "操作人", example = "管理员a")
    private String change_person;
    @ApiModelProperty(value = "说明", example = "无")
    private String remark;
    @ApiModelProperty(value = "变动时间", example = "2026-3-15")
    private String change_time;
}