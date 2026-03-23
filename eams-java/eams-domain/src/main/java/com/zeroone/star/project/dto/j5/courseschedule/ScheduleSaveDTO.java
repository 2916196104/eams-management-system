package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.Valid;
import java.time.LocalDate;
import java.util.List;

/*
* 描述：新增or修改排课计划参数对象
* */
@Data
public class ScheduleSaveDTO {
    @ApiModelProperty(value = "排课计划id 新增不传，修改必须传", example = "1")
    private Long id;

    @ApiModelProperty(value = "班级id",required = true , example = "1")
    private Long classId;

    @ApiModelProperty(value = "课程id,该字段在用户选择班级后，可以在对应班级的信息中找到",required = true, example = "1")
    private Long courseId;

    @ApiModelProperty(value = "教师id列表",required = true , example = "1,2")
    private String teacherIds;

    @ApiModelProperty(value = "助教id列表",required = false , example = "1,2")
    private String assistantIds;

    @ApiModelProperty(value = "开始日期",required = true,example = "2023-01-01")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期",required = true,example = "2023-01-01")
    private LocalDate endDate;

    @ApiModelProperty(value = "消课基数(学员扣课次数)，表示单人单次签到消课量，默认为1",example = "1")
    private Integer decLessonCount;

    @ApiModelProperty(value = "最多排课次数，不填按日期排满")
    private Integer times;

    @ApiModelProperty(value = "排课计划是否排除节假日",required = false,example = "true")
    private Boolean excludeHoliday;

    @ApiModelProperty(value = "排课计划设置列表",required = true,example = "一,二,三,四,五 14:00~18:00,")
    @Valid // <--- 关键！加上这个，才会去校验 List 里面每个对象的 @NotBlank
    private List<LessonScheduleSettingDTO> settingList;
}
