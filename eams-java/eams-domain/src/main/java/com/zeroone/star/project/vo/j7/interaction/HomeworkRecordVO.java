package com.zeroone.star.project.vo.j7.interaction;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：作业提交记录视图对象（返回前端）
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
@Data
@ApiModel("作业提交记录视图对象")
public class HomeworkRecordVO {

    @ApiModelProperty(value = "提交记录ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "所属作业ID", example = "1")
    private Long homeworkId;

    @ApiModelProperty(value = "学生ID", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "学生姓名", example = "李同学")
    private String studentName;

    @ApiModelProperty(value = "提交内容", example = "已完成所有练习题")
    private String content;

    @ApiModelProperty(value = "提交时间", example = "2026-03-15 14:30:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "评分", example = "90")
    private Integer score;

    @ApiModelProperty(value = "点评内容", example = "完成得很好")
    private String comment;

    @ApiModelProperty(value = "点评时间", example = "2026-03-15 16:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime commentTime;

    @ApiModelProperty(value = "点评老师姓名", example = "王老师")
    private String commentTeacherName;

    @ApiModelProperty(value = "附件图片URL", example = "http://xxx/img.jpg")
    private String images;
}
