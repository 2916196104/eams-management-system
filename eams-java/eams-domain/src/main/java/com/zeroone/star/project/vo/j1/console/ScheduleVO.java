package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel(value = "ScheduleVO", description = "课表日历视图对象")
public class ScheduleVO {

    @ApiModelProperty(value = "课表列表")
    private List<ScheduleItem> list;

    @Data
    @ApiModel(value = "ScheduleItem", description = "单条课表记录")
    public static class ScheduleItem {

        @ApiModelProperty(value = "主键ID")
        private Long id;

        @ApiModelProperty(value = "班级id")
        private Long classId;

        @ApiModelProperty(value = "课程id")
        private Long courseId;

        @ApiModelProperty(value = "上课老师（多个ID用逗号分隔）")
        private String teacherIds;

        @ApiModelProperty(value = "助教（多个ID用逗号分隔）")
        private String assistantIds;

        @ApiModelProperty(value = "开始日期")
        private LocalDate startDate;

        @ApiModelProperty(value = "结束日期")
        private LocalDate endDate;

        @ApiModelProperty(value = "学员扣课次数")
        private Integer decLessonCount;

        @ApiModelProperty(value = "排课次数")
        private Integer times;

        @ApiModelProperty(value = "排除节日")
        private Boolean excludeHoliday;

        @ApiModelProperty(value = "是否生成课表")
        private Boolean state;

        @ApiModelProperty(value = "创建人")
        private Long creator;

        @ApiModelProperty(value = "编辑者")
        private Long editor;

        @ApiModelProperty(value = "添加时间")
        private LocalDateTime addTime;

        @ApiModelProperty(value = "修改时间")
        private LocalDateTime editTime;

        @ApiModelProperty(value = "删除标记")
        private Boolean deleted;

        @ApiModelProperty(value = "冲突的id列表")
        private String conflictIds;

        @ApiModelProperty(value = "创建者所属组织ID")
        private Long orgId;

        // --- 关联查询/计算字段（非表字段） ---

        @ApiModelProperty(value = "上课时间（关联排课详情）")
        private LocalDateTime startTime;

        @ApiModelProperty(value = "课程名称（关联course表）")
        private String courseName;

        @ApiModelProperty(value = "班级名称（关联class表）")
        private String className;

        @ApiModelProperty(value = "上课老师名称（关联teacher表）")
        private String teacherName;

        @ApiModelProperty(value = "类型名称（字典转换）")
        private String typeName;

        @ApiModelProperty(value = "助教名称（关联teacher表）")
        private String assistantName;

        @ApiModelProperty(value = "教室（关联classroom表）")
        private String classroom;

        @ApiModelProperty(value = "可预约人数（计算字段）")
        private Integer reserveCount;

        @ApiModelProperty(value = "学生数（计算字段）")
        private Integer studentCount;

        @ApiModelProperty(value = "签到数（计算字段）")
        private Integer signCount;

        @ApiModelProperty(value = "到课率（计算字段）")
        private BigDecimal attendanceRate;

        @ApiModelProperty(value = "消课基数（计算字段）")
        private Integer lessonBase;

        @ApiModelProperty(value = "已消课数（计算字段）")
        private Integer lessonUsed;

        @ApiModelProperty(value = "上课情况（计算字段）")
        private String lessonStatus;

        @ApiModelProperty(value = "状态名称（字典转换）")
        private String stateName;
    }
}
