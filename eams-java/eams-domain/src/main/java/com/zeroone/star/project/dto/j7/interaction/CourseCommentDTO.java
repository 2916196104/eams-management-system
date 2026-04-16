// ==== DTO（CourseCommentDTO.java）====
package com.zeroone.star.project.dto.j7.interaction;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@ApiModel(value = "CourseCommentDTO", description = "教师点评学生-DTO（课程/课次点评）")
@Data
@TableName("course_comment")
public class CourseCommentDTO {
    @ApiModelProperty(value = "点评ID", example = "1")
    private Long id;

    @TableField("course_id")
    private Long courseId;

    @TableField("student_id")
    private Long studentId;

    @TableField("order_id")
    private Long orderId;

    @TableField("content")
    private String content;

    @TableField("score")
    private Integer score;

    @TableField("state")
    private Integer state;

    @TableField("creator")
    private Long creator; // 点评教师ID

    @TableField("editor")
    private Long editor;

    @TableField("add_time")
    private LocalDateTime addTime;

    @TableField("edit_time")
    private LocalDateTime editTime;

    @TableField("deleted")
    private Integer deleted;
}