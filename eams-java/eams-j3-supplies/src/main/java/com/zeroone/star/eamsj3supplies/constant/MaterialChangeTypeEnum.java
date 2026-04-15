package com.zeroone.star.eamsj3supplies.constant;

public enum MaterialChangeTypeEnum {
    INBOUND(1),
    OUTBOUND(2),
    POINTS_OUTBOUND(3);

    private final int code;

    MaterialChangeTypeEnum(int code) {
        this.code = code;
    }

    public int getCode() {
        return code;
    }

    public int toDelta(int amount) {
        return this == INBOUND ? amount : -amount;
    }

    public static MaterialChangeTypeEnum fromCode(Integer code) {
        if (code == null) {
            return null;
        }
        for (MaterialChangeTypeEnum value : values()) {
            if (value.code == code) {
                return value;
            }
        }
        return null;
    }
}
