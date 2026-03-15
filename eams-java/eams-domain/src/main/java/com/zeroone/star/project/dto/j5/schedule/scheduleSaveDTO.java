package com.zeroone.star.project.dto.j5.schedule;

import com.zeroone.star.project.po.schedule.LessonScheduleSettingPO;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

/*
* 描述：新增or修改排课计划参数对象
* */
@Data
public class scheduleSaveDTO {
    @ApiModelProperty(value = "排课计划id 新增不传，修改必须传", example = "1")
    private Long id;

    @ApiModelProperty(value = "班级id",required = true , example = "1")
    private Integer classId;

    @ApiModelProperty(value = "教师id列表",required = true , example = "1,2")
    private List<Long> teacherIds;

    @ApiModelProperty(value = "助教id列表",required = false , example = "1,2")
    private List<Long> assistantIds;

    @ApiModelProperty(value = "开始日期",required = true,example = "2023-01-01")
    private LocalDateTime startDate;

    @ApiModelProperty(value = "结束日期",required = true,example = "2023-01-01")
    private LocalDateTime endDate;

    @ApiModelProperty(value = "最多排课次数，不填按日期排满")
    private Integer times;

    @ApiModelProperty(value = "消课基数(学员扣课次数)，表示单人单次签到消课量，默认为1",required = true,example = "1")
    private Integer decLessonCount;

    @ApiModelProperty(value = "排课计划是否排除节假日",required = false,example = "true")
    private Boolean excludeHoliday;

    @ApiModelProperty(value = "排课计划设置列表",required = true,example = "一,二,三,四,五 14:00~18:00,")
    private List<LessonScheduleSettingPO> settingList;
}
