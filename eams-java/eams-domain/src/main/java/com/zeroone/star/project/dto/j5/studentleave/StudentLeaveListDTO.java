package com.zeroone.star.project.dto.j5.studentleave;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

/**
 * <p>
 * 描述：学员请假列表 DTO
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/15 16:22
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@ApiModel("学员请假列表DTO")
public class StudentLeaveListDTO {

    @ApiModelProperty(value = "请假表 id", example = "2008418408000000000")
    private Long id;

    @ApiModelProperty(value = "学员姓名", example = "小明")
    private String studentName;

    @ApiModelProperty(value = "电话", example = "13814754869")
    private String mobile;

    @ApiModelProperty(value = "请假课次(包含上课日期时间，以字符串形式输出)", example = "大学语文")
    private String courseInfo;

    @ApiModelProperty(value = "任课老师(可能多位)", example = "张三, 李四")
    private String teacherNames;

    @ApiModelProperty(value = "请假原因", example = "病假")
    private String reason;

    @ApiModelProperty(value = "请假时间", example = "2026-03-15 09:00")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "请假状态", example = "已撤销")
    private String state;

}