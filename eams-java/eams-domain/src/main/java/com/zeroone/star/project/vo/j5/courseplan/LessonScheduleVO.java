package com.zeroone.star.project.vo.j5.courseplan;

import com.zeroone.star.project.dto.j5.schedule.ScheduleSaveDTO;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/*
* 排课计划详情
* */
@Data
public class LessonScheduleVO extends ScheduleSaveDTO {
    @ApiModelProperty(value = "是否生成课表",example = "0" )
    private Integer state;

    @ApiModelProperty(value = "创建人id",example = "0" )
    private Long creator;

    @ApiModelProperty(value = "修改人id",example = "0" )
    private Long editor;

    @ApiModelProperty(value = "创建时间",example = "2023-01-01" )
    private LocalDateTime addTime;

    @ApiModelProperty(value = "修改时间",example = "2023-01-01" )
    private LocalDateTime editTime;

    @ApiModelProperty(value = "删除状态",example = "0" )
    private Integer deleted;

    @ApiModelProperty(value = "冲突的id列表 空字符表示无冲突 null表示未检查")
    private String conflictIds;

    @ApiModelProperty(value = "创建者所属组织id")
    private Long orgId;
}
