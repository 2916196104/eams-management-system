package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;

@Data
@ApiModel("课后点评列表返回视图对象")
public class EvaluationVO {



        private static final long serialVersionUID = 1L;

        @ApiModelProperty(value = "点评记录ID", example = "1")
        private Long id;

        @ApiModelProperty(value = "学员ID", example = "1001")
        private Long studentId;

        @ApiModelProperty(value = "学员姓名", example = "张小明")
        private String studentName;

        @ApiModelProperty(value = "学员手机号（脱敏）", example = "138****0001")
        private String studentPhone;

        @ApiModelProperty(value = "点评得分", example = "95")
        private Integer commentScore;

        @ApiModelProperty(value = "点评内容", example = "课堂表现积极，知识点掌握牢固")
        private String commentContent;

        @ApiModelProperty(value = "点评老师ID", example = "2001")
        private Long teacherId;

        @ApiModelProperty(value = "点评老师姓名", example = "李老师")
        private String teacherName;

        @ApiModelProperty(value = "点评时间", example = "2026-03-23 14:30:00")
        private String commentTime;

}
