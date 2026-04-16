package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import java.time.LocalDateTime;

@Data
@ApiModel("课程评价数据")
public class CourseCommentDTO {
    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "所属课程ID", example = "101", required = true)
    private Long courseId;

    @ApiModelProperty(value = "学生ID", example = "201", required = true)
    private Long studentId;

    @ApiModelProperty(value = "订单ID", example = "301")
    private Long orderId;

    @NotBlank(message = "评价内容不能为空")
    @ApiModelProperty(value = "评价内容", example = "课程非常棒，老师讲解很详细", required = true)
    private String content;

    @ApiModelProperty(value = "评分(1-5)", example = "5")
    private Integer score = 5;

    @ApiModelProperty(value = "发布状态: 0-未发布, 1-已发布", example = "0")
    private Integer state = 0;

    @ApiModelProperty(value = "创建人ID", example = "1001")
    private Long creator;

    @ApiModelProperty(value = "编辑人ID", example = "1002")
    private Long editor;

    @ApiModelProperty(value = "添加时间", example = "2024-01-15 10:30:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "编辑时间", example = "2024-01-20 14:30:00")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "删除标记: 0-未删除, 1-已删除", example = "0")
    private Integer deleted = 0;

}
