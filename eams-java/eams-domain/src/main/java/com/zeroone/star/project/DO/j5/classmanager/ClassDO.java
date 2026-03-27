package com.zeroone.star.project.DO.j5.classmanager;

import com.baomidou.mybatisplus.annotation.TableField;
import io.github.classgraph.json.Id;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import com.baomidou.mybatisplus.annotation.TableName;

import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@TableName("class")
public class ClassDO {
    @Id
    @ApiModelProperty(value = "主键", example = "1")
    private Long id;

    @ApiModelProperty(value = "班级名", example = "三年二班")
    private String name;
    @TableField("course_id")
    @ApiModelProperty(value = "课程ID", example = "5")
    private Long courseId;
    @ApiModelProperty(value = "教室ID", example = "10")
    private Long classroomId;

    @ApiModelProperty(value = "创建人", example = "1")
    private Long creator;

    @ApiModelProperty(value = "编辑者", example = "1")
    private Long editor;

    @ApiModelProperty(value = "添加时间", example = "2023-01-01 10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "编辑时间", example = "2023-01-02 11:00:00")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "删除标记", example = "false")
    private Boolean deleted;
    @ApiModelProperty(value = "班级负责人", example = "3")
    private Long teacherId;

    @ApiModelProperty(value = "排课备注", example = "数学强化班")
    private String remark;

    @ApiModelProperty(value = "是否完结", example = "0", notes = "0表示未完结，1表示完结")
    private Integer beOver;
    @ApiModelProperty(value = "完结时间", example = "2023-06-30 18:00:00")
    private LocalDateTime overTime;
    @ApiModelProperty(value = "完结操作人", example = "1")
    private Long overOperator;

    @ApiModelProperty(value = "计划开班日期", example = "2023-03-01")
    private LocalDate startDate;

    @ApiModelProperty(value = "计划结业日期", example = "2023-07-01")
    private LocalDate endDate;

    @ApiModelProperty(value = "预招人数", example = "30")
    private Integer plannedStudentCount;

    @ApiModelProperty(value = "预排课次数", example = "20")
    private Integer plannedLessonCount;
    @ApiModelProperty(value = "创建者所属学校id", example = "100")
    private Long schoolId;

    @ApiModelProperty(value = "创建者所属组织ID", example = "200")
    private Long orgId;
    @ApiModelProperty(value = "年级ID", example = "2")
    private Integer gradeId;

}
