package com.zeroone.star.project.vo.j7.interaction;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

/**
 * <p>
 * 描述：作业视图对象（返回前端）
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
@Data
@ApiModel("作业视图对象")
public class HomeworkVO {

    @ApiModelProperty(value = "作业ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "班级ID", example = "1")
    private Long classId;

    @ApiModelProperty(value = "班级名称", example = "Java高级班")
    private String className;

    @ApiModelProperty(value = "标题", example = "第一次课后作业")
    private String title;

    @ApiModelProperty(value = "内容", example = "完成Spring Boot基础练习")
    private String content;

    @ApiModelProperty(value = "创建人ID（教师）", example = "1")
    private Long creator;

    @ApiModelProperty(value = "教师姓名", example = "张老师")
    private String teacherName;

    @ApiModelProperty(value = "添加时间", example = "2026-03-15 10:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "已提交人数", example = "15")
    private Integer completeCount;

    @ApiModelProperty(value = "当前学生是否已完成", example = "true")
    private Boolean completed;

    @ApiModelProperty(value = "提交记录列表（详情接口嵌套返回）")
    private List<com.zeroone.star.project.vo.j7.interaction.HomeworkRecordVO> recordList;
}
