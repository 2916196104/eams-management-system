package com.zeroone.star.project.vo.j5.studentleave;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

/**
 * <p>
 * 描述：查询学生请假列表中间类
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/25 21:45
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class StudentLeaveListVO {

    private Long id;

    private String studentName;

    private String mobile;

    private String course;

    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate date;

    @DateTimeFormat(pattern = "HH:mm")
    private LocalTime startTime;

    @DateTimeFormat(pattern = "HH:mm")
    private LocalTime endTime;

    private String teacherNames;

    private String reason;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm")
    private LocalDateTime addTime;

    private String state;

    /**
     * 获取拼接后的课程信息字符串
     * 格式：课程名 日期 开始时间-结束时间
     */
    public String getCourseInfo() {
        if (course == null) {
            return "";
        }

        StringBuilder sb = new StringBuilder(course);

        if (date != null) {
            sb.append(" ").append(date.toString());
        }

        if (startTime != null && endTime != null) {
            sb.append(" ")
                    .append(startTime.toString())
                    .append("-")
                    .append(endTime.toString());
        } else if (startTime != null) {
            sb.append(" ").append(startTime.toString());
        }

        return sb.toString();
    }

}
