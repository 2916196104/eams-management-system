package com.zeroone.star.project.eums;

import com.baomidou.mybatisplus.annotation.EnumValue;
import com.fasterxml.jackson.annotation.JsonValue;

public enum WeekdaysEnum implements BaseEnum {
    MON(1, "一"),
    TUE(2, "二"),
    WED(3, "三"),
    THU(4, "四"),
    FRI(5, "五"),
    SAT(6, "六"),
    SUN(7, "日");

    @EnumValue
    private final int code;
    @JsonValue
    private final String name;

    public int getCode() {
        return this.code;
    }

    public String getName() {
        return this.name;
    }

    private WeekdaysEnum(final int code, final String name) {
        this.code = code;
        this.name = name;
    }
}

