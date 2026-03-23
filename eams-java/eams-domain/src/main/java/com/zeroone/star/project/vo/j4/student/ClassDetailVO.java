package com.zeroone.star.project.vo.j4.student;
import lombok.Data;

/**
 * 班级详情查询 VO（内部使用）
 */
@Data
public class ClassDetailVO {
    private Long id;
    private String name;
    private Long courseId;
    private Long classroomId;
    private String classroomName;
    private String subject;
    private Integer studentCount;
    private Integer plannedStudentCount;
}