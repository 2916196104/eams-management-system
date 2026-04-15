package com.zeroone.star.project.enums;

import com.baomidou.mybatisplus.annotation.EnumValue;
import lombok.AllArgsConstructor;
import lombok.Getter;

import java.util.Arrays;

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

    /**
     * 根据code获取枚举
     */
    public static SignStateEnum getByCode(Integer code) {
        if (code == null) {
            return null;
        }
        return Arrays.stream(values())
                .filter(e -> e.code.equals(code))
                .findFirst()
                .orElse(null);
    }
}
