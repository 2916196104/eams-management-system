package com.zeroone.star.project.vo;

public enum ResultStatus {
    UNAUTHORIZED("Unauthorized or token expired", 401),
    FORBIDDEN("Forbidden", 403),
    SERVER_ERROR("Server error", 9994),
    PARAMS_INVALID("Invalid params", 9995),
    CONTENT_TYPE_ERR("Invalid content type", 9996),
    API_UN_IMPL("API not implemented", 9997),
    SERVER_BUSY("Server busy", 9998),
    FAIL("Operation failed", 9999),
    SUCCESS("Operation succeeded");

    private final String message;
    private final int code;

    ResultStatus(String message, int code) {
        this.message = message;
        this.code = code;
    }

    ResultStatus(String message) {
        this(message, 10000);
    }

    public String getMessage() {
        return message;
    }

    public int getCode() {
        return code;
    }
}
