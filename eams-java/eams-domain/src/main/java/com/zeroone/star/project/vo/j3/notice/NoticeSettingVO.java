package com.zeroone.star.project.vo.j3.notice;

import lombok.Data;

@Data
public class NoticeSettingVO<T> {
    private int code;
    private String msg;
    private T data;

    public void JsonVO(int code, String msg, T data) {
        this.code = code;
        this.msg = msg;
        this.data = data;
    }

    public void JsonVO(int code, String msg) {
        this.code = code;
        this.msg = msg;
    }

    public void JsonVO() {
    }

}
