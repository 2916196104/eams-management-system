package com.zeroone.star.project.DO.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel(description = "班级DO")
public class ClassDo {

        @ApiModelProperty(value = "ID")
        private Long id;
        @ApiModelProperty(value = "班级名称")
        private String name;
        @ApiModelProperty(value = "课程ID")
        private Long courseId;
        @ApiModelProperty(value = "教室ID")
        private Long classroomId;
        @ApiModelProperty(value = "创建人")
        private Long creator;
        @ApiModelProperty(value = "编辑人")
        private Long editor;
        @ApiModelProperty(value = "创建时间")
        private LocalDateTime addTime;
        @ApiModelProperty(value = "编辑时间")
        private LocalDateTime editTime;
        @ApiModelProperty(value = "删除标记")
        private Integer deleted;
        @ApiModelProperty(value = "教师ID")
        private Long teacherId;
        @ApiModelProperty(value = "备注")
        private String remark;
        @ApiModelProperty(value = "是否结课")
        private Integer beOver;
        @ApiModelProperty(value = "结课时间")
        private LocalDateTime overTime;
        @ApiModelProperty(value = "结课操作人")
        private Long overOperator;
        @ApiModelProperty(value = "开始日期")
        private LocalDate startDate;
        @ApiModelProperty(value = "结束日期")
        private LocalDate endDate;
        @ApiModelProperty(value = "计划人数")
        private Integer plannedStudentCount;
        @ApiModelProperty(value = "计划课次")
        private Integer plannedLessonCount;
        @ApiModelProperty(value = "学校ID")
        private Long schoolId;
        @ApiModelProperty(value = "机构ID")
        private Long orgId;
        @ApiModelProperty(value = "年级ID")
        private Long gradeId;
}
