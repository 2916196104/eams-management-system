package com.zeroone.star.project.vo.j3.data;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class StudentLessonCountsVO {
    @ApiModelProperty(value = "学生名字", example = "周杰伦")
    private String studentName;

    @ApiModelProperty(value = "课时消耗记录", example = "20")
    private int lessonCount;

    @ApiModelProperty(value = "学生ID")
    private Long studentId;

    @ApiModelProperty(value = "学生排名", example = "12")
    private int studentRank;
}
