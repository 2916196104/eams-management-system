package com.zeroone.star.project.enums;

import com.baomidou.mybatisplus.annotation.EnumValue;
import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public enum SignStateEnum {
    NONE(0, "未签到"),
    NORMAL(1, "已签到"),
    LATE(2, "迟到签到"),
    LEAVE(3, "请假"),
    ABSENT(4, "旷课");

    @EnumValue
    private final Integer code;
    private final String desc;
}
