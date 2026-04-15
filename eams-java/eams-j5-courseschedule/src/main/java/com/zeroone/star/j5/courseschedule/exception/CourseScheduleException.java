package com.zeroone.star.j5.courseschedule.exception;

/**
 * 课程编排模块运行时异常
 */
public class CourseScheduleException extends RuntimeException {

    private final CourseScheduleErrorCode errorCode;

    public CourseScheduleException(CourseScheduleErrorCode errorCode, String message) {
        super(message);
        this.errorCode = errorCode;
    }

    public CourseScheduleErrorCode getErrorCode() {
        return errorCode;
    }
}
