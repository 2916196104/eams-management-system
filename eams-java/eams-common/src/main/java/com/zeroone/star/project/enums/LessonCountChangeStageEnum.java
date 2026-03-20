package com.zeroone.star.project.enums;

import com.baomidou.mybatisplus.annotation.EnumValue;
import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public enum LessonCountChangeStageEnum {
    CONTRACT(1, "课程报名"),
    LESSON_DEC(2, "上课消课"),
    ADMIN(3, "后台操作"),
    REFUND(4, "退课"),
    REFUND_REJECT(5, "退课驳回"),
    ROLLBACK(6, "取消消课");

    @EnumValue
    private final Integer code;
    private final String desc;
}
