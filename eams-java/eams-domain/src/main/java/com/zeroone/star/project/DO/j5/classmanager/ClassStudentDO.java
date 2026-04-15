package com.zeroone.star.project.DO.j5.classmanager;

import com.baomidou.mybatisplus.annotation.TableName;
import io.github.classgraph.json.Id;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("class_student")
@ApiModel(description = "班级学员实体")
public class ClassStudentDO {

    @Id
    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "所属班级ID", example = "5")
    private Long classId;

    @ApiModelProperty(value = "学生ID", example = "1")
    private Long studentId;


    @ApiModelProperty(value = "添加时间", example = "2023-01-01 10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "删除标记", example = "false")
    private Integer deleted;

    @ApiModelProperty(value = "创建者", example = "5")
    private Long creator;
    @ApiModelProperty(value = "加入原因", example = "5")
    private Integer reason;
    @ApiModelProperty(value = "备注信息", example = "5")
    private String remark;
    @ApiModelProperty(value = "默认消费课程", example = "5")
    private Long consume_course_id;
}
