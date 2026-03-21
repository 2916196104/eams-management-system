package com.zeroone.star.student.entity;

import java.time.LocalDateTime;

/**
 * student_Credit_Log
 */
public class StudentCreditLog {
    private int id;

    private int studentId;

    private int userId;

    private int credit;

    private int current_credit;

    private int changeType;

    private LocalDateTime addTime;

    private String remark;

    private int sourceId;

    private int staffId;

    private int schoolId;
}
