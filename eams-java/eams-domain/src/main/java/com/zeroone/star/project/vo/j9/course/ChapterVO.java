package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：章节显示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Data
@ApiModel("章节显示对象")
public class ChapterVO {
    @ApiModelProperty(value = "章节ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "章节名称", example = "第一章")
    private String name;

    @ApiModelProperty(value = "课程ID", example = "1")
    private Long courseId;

    @ApiModelProperty(value = "排序", example = "1")
    private Integer sort;

    @ApiModelProperty(value = "创建时间", example = "2023-10-01 12:00:00")
    private LocalDateTime createTime;

    @ApiModelProperty(value = "更新时间", example = "2023-10-01 12:00:00")
    private LocalDateTime updateTime;

    @ApiModelProperty(value = "计划课时数", example = "8")
    private Integer lessonCount;
}