package com.zeroone.star.project.constant;

/**
 * 自动填充相关常量
 */
public interface AutoFillConstant {
    /**
     * 实体类中的方法名（对应数据库字段：creator, editor, add_time, edit_time）
     */
    String SET_CREATE_TIME = "setAddTime";
    String SET_UPDATE_TIME = "setEditTime";
    String SET_CREATE_USER = "setCreator";
    String SET_UPDATE_USER = "setEditor";
}
