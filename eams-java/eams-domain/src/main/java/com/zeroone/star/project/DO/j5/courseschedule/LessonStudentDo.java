package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel(description = "课次学生DO")
public class LessonStudentDo {
    @ApiModelProperty(value = "ID")
    private Long id;
    @ApiModelProperty(value = "课次ID")
    private Long lessonId;
    @ApiModelProperty(value = "班级ID")
    private Long classId;
    @ApiModelProperty(value = "学生ID")
    private Long studentId;
    @ApiModelProperty(value = "扣课次数")
    private Integer decLessonCount;
    @ApiModelProperty(value = "课次数量")
    private Integer lessonCount;
    @ApiModelProperty(value = "教师ID")
    private Long teacherId;
    @ApiModelProperty(value = "签到时间")
    private LocalDateTime signTime;
    @ApiModelProperty(value = "签到类型")
    private Integer signType;
    @ApiModelProperty(value = "签到状态")
    private Integer signState;
    @ApiModelProperty(value = "分数")
    private Integer score;
    @ApiModelProperty(value = "评价")
    private String evaluation;
    @ApiModelProperty(value = "评价时间")
    private LocalDateTime evaluateTime;
    @ApiModelProperty(value = "评价教师")
    private Long evaluateTeacher;
    @ApiModelProperty(value = "消费课程ID")
    private Long consumeCourseId;
    @ApiModelProperty(value = "学员课程ID")
    private Long consumeStudentCourseId;
    @ApiModelProperty(value = "课程顾问")
    private Long counselor;
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;
    @ApiModelProperty(value = "机构ID")
    private Long orgId;
}
