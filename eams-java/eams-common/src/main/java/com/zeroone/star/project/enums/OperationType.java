package com.zeroone.star.project.enums;

import lombok.AllArgsConstructor;
import lombok.Getter;

/**
 * 数据库操作类型枚举
 */
@Getter
@AllArgsConstructor
public enum OperationType {
    /**
     * 插入操作
     */
    INSERT,
    
    /**
     * 更新操作
     */
    UPDATE
}
