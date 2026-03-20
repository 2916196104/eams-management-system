package com.zeroone.star.j5.courseschedule.exception;

/**
 * Runtime exception skeleton for course schedule module.
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

