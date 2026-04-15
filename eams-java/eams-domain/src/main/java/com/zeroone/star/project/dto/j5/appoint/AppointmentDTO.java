package com.zeroone.star.project.dto.j5.appoint;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.io.Serializable;
import java.time.LocalDateTime;
import com.fasterxml.jackson.annotation.JsonFormat;

/**
 * 预约记录列表展示 DTO
 */
@Data
public class AppointmentDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "主键ID", example = "101")
    private Long id;

    @ApiModelProperty(value = "学生姓名", example = "Peggy Jordan")
    private String studentName;

    @ApiModelProperty(value = "手机号", example = "13800138000")
    private String mobile;

    @ApiModelProperty(value = "课程名称", example = "少儿英语启蒙班")
    private String courseName;

    @ApiModelProperty(value = "上课时间", example = "2026-03-20 10:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm")
    private LocalDateTime lessonTime;

    @ApiModelProperty(value = "预约时间", example = "2000-07-02 03:31")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "审核状态值(1-待审核, 2-通过, 3-驳回)", example = "2")
    private Integer verifyState;


    @ApiModelProperty(value = "备注", example = "2KJNEONJXP")
    private String remark;

}