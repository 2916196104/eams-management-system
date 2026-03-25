package com.zeroone.star.sysmanager.handler;

import com.zeroone.star.sysmanager.exception.BusinessException;
import com.zeroone.star.project.vo.JsonVO;  // 你们项目已有的 JsonVO
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

/**
 * 全局异常处理器
 */
@Slf4j
@RestControllerAdvice
public class GlobalExceptionHandler {

    /**
     * 处理业务异常
     */
    @ExceptionHandler(BusinessException.class)
    public JsonVO<?> handleBusinessException(BusinessException e) {
        log.error("业务异常：{}", e.getMessage());
        // 返回错误信息，JsonVO
        return JsonVO.fail(e.getMessage());
    }

    /**
     * 处理其他所有异常（兜底）
     */
    @ExceptionHandler(Exception.class)
    public JsonVO<?> handleException(Exception e) {
        log.error("系统异常：", e);
        return JsonVO.fail("系统繁忙，请稍后再试");
    }
}