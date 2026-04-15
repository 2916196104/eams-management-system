package com.zeroone.star.project.query.j5.courseschedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.NotNull;
import java.time.LocalDate;

@Data
public class EvaluationQuery extends PageQuery {

    @ApiModelProperty("课程ID")
    @NotNull(message = "课程ID不能为空")
    private Long lessonId;

    @ApiModelProperty("是否仅查询已评价的记录")
    private Boolean onlyEvaluate = false;


//    @ApiModelProperty("评价内容（模糊查询）")
//    private String evaluateContent;
//
//    @ApiModelProperty("班级ID")
//    private Long classId;
//    @ApiModelProperty("班级名称（模糊查询）")
//    private String className;
//
//    @ApiModelProperty("课程ID")
//    private Long courseId;
//    @ApiModelProperty("课程名称（模糊查询）")
//    private String courseName;
//
//    @ApiModelProperty("课次ID（选中的课次）")
//    private Long lessonId;
//    @ApiModelProperty("课次日期（用于按日期范围筛选课次）")
//    private String lessonDate;
//    @ApiModelProperty("课次时间范围开始")
//    private String lessonStartTime;
//    @ApiModelProperty("课次时间范围结束")
//    private String lessonEndTime;
//
//    @ApiModelProperty(value = "老师ID",required = false,example = "1")
//    private String teacherId;
//    @ApiModelProperty(value = "老师姓名",required = false,example = "张三")
//    private String teacherName;
//
//    @ApiModelProperty(value = "学生ID",required = false,example = "1")
//    private String id;
//    @ApiModelProperty(value = "学生姓名",required = false,example = "小明")
//    private String name;

}
