package com.zeroone.star.login.config;

import com.zeroone.star.login.exception.LoginException;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import lombok.extern.slf4j.Slf4j;
import org.springframework.validation.BindException;
import org.springframework.validation.FieldError;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.MissingServletRequestParameterException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

import javax.validation.ConstraintViolation;
import javax.validation.ConstraintViolationException;
import java.util.stream.Collectors;

@RestControllerAdvice
@Slf4j
public class GlobalExceptionHandler {

    @ExceptionHandler(MethodArgumentNotValidException.class)
    public JsonVO<Void> handleMethodArgumentNotValidException(MethodArgumentNotValidException e) {
        String message = e.getBindingResult().getFieldErrors().stream()
                .map(FieldError::getDefaultMessage)
                .collect(Collectors.joining("; "));
        log.warn("Parameter validation failed: {}", message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    @ExceptionHandler(BindException.class)
    public JsonVO<Void> handleBindException(BindException e) {
        String message = e.getBindingResult().getFieldErrors().stream()
                .map(FieldError::getDefaultMessage)
                .collect(Collectors.joining("; "));
        log.warn("Parameter binding failed: {}", message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    @ExceptionHandler(ConstraintViolationException.class)
    public JsonVO<Void> handleConstraintViolationException(ConstraintViolationException e) {
        String message = e.getConstraintViolations().stream()
                .map(ConstraintViolation::getMessage)
                .collect(Collectors.joining("; "));
        log.warn("Constraint validation failed: {}", message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    @ExceptionHandler(MissingServletRequestParameterException.class)
    public JsonVO<Void> handleMissingServletRequestParameterException(MissingServletRequestParameterException e) {
        String message = "Missing required parameter: " + e.getParameterName();
        log.warn(message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    @ExceptionHandler(LoginException.class)
    public JsonVO<Void> handleLoginException(LoginException e) {
        log.warn("Login business exception: {}", e.getMessage());
        return JsonVO.create(null, ResultStatus.FAIL.getCode(), e.getMessage());
    }

    @ExceptionHandler(RuntimeException.class)
    public JsonVO<Void> handleRuntimeException(RuntimeException e) {
        log.error("Runtime exception: {}", e.getMessage(), e);
        return JsonVO.create(null, ResultStatus.FAIL.getCode(), e.getMessage());
    }

    @ExceptionHandler(Exception.class)
    public JsonVO<Void> handleException(Exception e) {
        log.error("Unexpected exception: {}", e.getMessage(), e);
        return JsonVO.create(null, ResultStatus.SERVER_ERROR.getCode(), "System busy, please try again later");
    }
}
