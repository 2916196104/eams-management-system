package com.zeroone.star.project.j1.orgmanager.handler;

import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.converter.HttpMessageNotReadableException;
import org.springframework.validation.BindException;
import org.springframework.validation.ObjectError;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

import javax.validation.ConstraintViolationException;

/**
 * <p>
 * 描述：组织管理模块统一异常处理
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@RestControllerAdvice(basePackages = "com.zeroone.star.project.j1.orgmanager")
public class GlobalExceptionHandler {
    @ExceptionHandler(MethodArgumentNotValidException.class)
    public JsonVO<String> handleMethodArgumentNotValidException(MethodArgumentNotValidException exception) {
        ObjectError error = exception.getBindingResult().getAllErrors().stream().findFirst().orElse(null);
        return JsonVO.fail(error == null ? "参数校验失败" : error.getDefaultMessage());
    }

    @ExceptionHandler(BindException.class)
    public JsonVO<String> handleBindException(BindException exception) {
        ObjectError error = exception.getBindingResult().getAllErrors().stream().findFirst().orElse(null);
        return JsonVO.fail(error == null ? "参数绑定失败" : error.getDefaultMessage());
    }

    @ExceptionHandler(ConstraintViolationException.class)
    public JsonVO<String> handleConstraintViolationException(ConstraintViolationException exception) {
        return JsonVO.fail(exception.getMessage());
    }

    @ExceptionHandler(HttpMessageNotReadableException.class)
    public JsonVO<String> handleHttpMessageNotReadableException(HttpMessageNotReadableException exception) {
        return JsonVO.fail("请求体格式错误");
    }

    @ExceptionHandler(IllegalArgumentException.class)
    public JsonVO<String> handleIllegalArgumentException(IllegalArgumentException exception) {
        return JsonVO.fail(exception.getMessage());
    }

    @ExceptionHandler(Exception.class)
    public JsonVO<String> handleException(Exception exception) {
        return JsonVO.fail(exception.getMessage() == null ? "系统异常" : exception.getMessage());
    }
}
