package com.zeroone.star.project.enums;

import com.baomidou.mybatisplus.annotation.EnumValue;
import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public enum LessonStateEnum {
    STOPPED(0, "已停课"),
    UNDERWAY(1, "进行中"),
    COMPLETE(2, "已结课");

    @EnumValue
    private final Integer code;
    private final String desc;
}
