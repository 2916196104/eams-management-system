package com.zeroone.star.project.vo.j8.stumanager;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 学生表vo
 * </p>
 *
 * @author 541720500@qq.com
 */
@Data
public class StudentCourseVO implements Serializable {
    private Long id;

    private Long studentId;

    private String studentName;

    private Long courseId;

    private String courseName;

    private String subjectName;

    private Integer countLessonTotal;

    private Integer countLessonComplete;

    private Integer countLessonRemaining;

}
