package com.zeroone.star.project.vo.j8.stumanager;

import com.baomidou.mybatisplus.annotation.EnumValue;
import com.fasterxml.jackson.annotation.JsonValue;
import lombok.Getter;

@Getter
public enum FamilyRelEnum {

    FATHER("父亲"),
    MOTHER("母亲"),
    SON("儿子"),
    DAUGHTER("女儿"),
    GRANDFATHER("祖父"),
    GRANDMOTHER("祖母");

    @EnumValue
    private final String code;

    @JsonValue
    private final String text;

    FamilyRelEnum(String text) {
        this.code = text;
        this.text = text;
    }
}