
package com.zeroone.star.project.vo.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDate;
import io.swagger.annotations.ApiModel;
/**
 * <p>
 * 描述：员工带班记录展示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author chichu
 * @version 1.0.0
 */


@Data
@ApiModel(value = "TeachRecordVO", description = "所带班级VO")
public class ClassRecordVO {

//    @ApiModelProperty(value = "班级ID", example = "3001")
//    private Long classId;

    @ApiModelProperty(value = "班级名称", example = "三年级一班", required = true)
    private String className;

    @ApiModelProperty(value = "课程名称", example = "数学同步班", required = true)
    private String courseName;

    @ApiModelProperty(value = "科目名称", example = "数学", required = true)
    private String subjectName;

    @ApiModelProperty(value = "教室名称", example = "一楼103教室")
    private String classroomName;

    @ApiModelProperty(value = "班主任", example = "李老师")
    private String teacherName;

    @ApiModelProperty(value = "学生人数", example = "25")
    private Integer studentCount;

    @ApiModelProperty(value = "预招人数", example = "30")
    private Integer plannedStudentCount;

    @ApiModelProperty(value = "计划课次", example = "40")
    private Integer plannedLessonCount;

    @ApiModelProperty(value = "已上/已排课", example = "10/15")
    private String lessonSchedule;

    @ApiModelProperty(value = "上课进度", example = "25%")
    private String lessonProgress;

    @ApiModelProperty(value = "排课备注", example = "每周一三五上课")
    private String remark;

    @ApiModelProperty(value = "开班时间", example = "2025-09-01")
    private LocalDate startDate;

    @ApiModelProperty(value = "结业时间", example = "2026-01-10")
    private LocalDate endDate;

    @ApiModelProperty(value = "班级状态", example = "正常")
    private String statusName;
}
//package com.zeroone.star.project.vo.j1.org;
//
//import io.swagger.annotations.ApiModelProperty;
//import lombok.AllArgsConstructor;
//import lombok.Builder;
//import lombok.Data;
//import lombok.NoArgsConstructor;
//import java.time.LocalDate;
//
///**
// * <p>
// * 描述：员工带班记录展示对象
// * </p>
// * <p>版权：&copy;01星球</p>
// * <p>地址：01星球总部</p>
// * @author chichu
// * @version 1.0.0
// */
//@Data
//@Builder
//@NoArgsConstructor
//@AllArgsConstructor
//public class ClassRecordVO {
//    @ApiModelProperty(value = "班级名称", example = "2026春季Java班")
//    private String className;
//
//    @ApiModelProperty(value = "课程名称", example = "Java后端开发")
//    private String courseName;
//
//    @ApiModelProperty(value = "学生人数", example = "30")
//    private Integer studentCount;
//
//    @ApiModelProperty(value = "开班时间", example = "2026-02-15")
//    private LocalDate startDate;
//
//    @ApiModelProperty(value = "上课进度", example = "50%")
//    private String progress;
//}