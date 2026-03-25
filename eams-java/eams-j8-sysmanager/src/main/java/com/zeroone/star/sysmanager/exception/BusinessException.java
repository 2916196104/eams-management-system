package com.zeroone.star.sysmanager.exception;


    /**
     * 业务异常类
     */

import lombok.Getter;

    @Getter
    public class BusinessException extends RuntimeException {

        private Integer code;
        private String message;

        public BusinessException(String message) {
            super(message);
            this.message = message;
            this.code = 500;  // 默认错误码
        }

        public BusinessException(Integer code, String message) {
            super(message);
            this.code = code;
            this.message = message;
        }


}
