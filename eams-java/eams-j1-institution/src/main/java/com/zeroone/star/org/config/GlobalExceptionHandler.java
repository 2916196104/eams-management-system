package com.zeroone.star.org.config;

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

/**
 * 全局异常处理器
 */
@RestControllerAdvice
@Slf4j
public class GlobalExceptionHandler {

    /**
     * 处理参数校验异常（@Valid @RequestBody）
     */
    @ExceptionHandler(MethodArgumentNotValidException.class)
    public JsonVO<Void> handleMethodArgumentNotValidException(MethodArgumentNotValidException e) {
        String message = e.getBindingResult().getFieldErrors().stream()
                .map(FieldError::getDefaultMessage)
                .collect(Collectors.joining("; "));
        log.warn("参数校验失败: {}", message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    /**
     * 处理参数校验异常（@Valid 表单）
     */
    @ExceptionHandler(BindException.class)
    public JsonVO<Void> handleBindException(BindException e) {
        String message = e.getBindingResult().getFieldErrors().stream()
                .map(FieldError::getDefaultMessage)
                .collect(Collectors.joining("; "));
        log.warn("参数绑定失败: {}", message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    /**
     * 处理参数校验异常（@Validated 方法参数）
     */
    @ExceptionHandler(ConstraintViolationException.class)
    public JsonVO<Void> handleConstraintViolationException(ConstraintViolationException e) {
        String message = e.getConstraintViolations().stream()
                .map(ConstraintViolation::getMessage)
                .collect(Collectors.joining("; "));
        log.warn("约束校验失败: {}", message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    /**
     * 处理缺少请求参数异常
     */
    @ExceptionHandler(MissingServletRequestParameterException.class)
    public JsonVO<Void> handleMissingServletRequestParameterException(MissingServletRequestParameterException e) {
        String message = "缺少必要参数: " + e.getParameterName();
        log.warn(message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    /**
     * 处理业务运行时异常
     */
    @ExceptionHandler(RuntimeException.class)
    public JsonVO<Void> handleRuntimeException(RuntimeException e) {
        log.error("业务异常: {}", e.getMessage(), e);
        return JsonVO.create(null, ResultStatus.FAIL.getCode(), e.getMessage());
    }

    /**
     * 处理其他未知异常
     */
    @ExceptionHandler(Exception.class)
    public JsonVO<Void> handleException(Exception e) {
        log.error("系统异常: {}", e.getMessage(), e);
        return JsonVO.create(null, ResultStatus.SERVER_ERROR.getCode(), "系统繁忙，请稍后重试");
    }
}
