package com.zeroone.star.project.j1.orgmanager.handler;

import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.converter.HttpMessageNotReadableException;
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
 * 统一全局异常处理器（合并版）
 */
@RestControllerAdvice(basePackages = "com.zeroone.star.project.j1.orgmanager")
@Slf4j
public class GlobalExceptionHandler {

    /**
     * 处理 @RequestBody 参数校验异常
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
     * 处理表单参数绑定异常
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
     * 处理 @Validated 方法参数校验异常
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
     * 缺少请求参数异常
     */
    @ExceptionHandler(MissingServletRequestParameterException.class)
    public JsonVO<Void> handleMissingServletRequestParameterException(MissingServletRequestParameterException e) {
        String message = "缺少必要参数: " + e.getParameterName();
        log.warn(message);
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), message);
    }

    /**
     * 请求体格式错误（JSON格式不对）
     */
    @ExceptionHandler(HttpMessageNotReadableException.class)
    public JsonVO<Void> handleHttpMessageNotReadableException(HttpMessageNotReadableException e) {
        log.warn("请求体格式错误");
        return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), "请求体格式错误");
    }

    /**
     * 非法参数异常
     */
    @ExceptionHandler(IllegalArgumentException.class)
    public JsonVO<Void> handleIllegalArgumentException(IllegalArgumentException e) {
        log.error("参数异常: {}", e.getMessage());
        return JsonVO.create(null, ResultStatus.FAIL.getCode(), e.getMessage());
    }

    /**
     * 业务异常
     */
    @ExceptionHandler(RuntimeException.class)
    public JsonVO<Void> handleRuntimeException(RuntimeException e) {
        log.error("业务异常: {}", e.getMessage(), e);
        return JsonVO.create(null, ResultStatus.FAIL.getCode(), e.getMessage());
    }

    /**
     * 兜底：系统未知异常
     */
    @ExceptionHandler(Exception.class)
    public JsonVO<Void> handleException(Exception e) {
        log.error("系统异常: {}", e.getMessage(), e);
        return JsonVO.create(null, ResultStatus.SERVER_ERROR.getCode(), "系统繁忙，请稍后重试");
    }
}