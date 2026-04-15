package com.zeroone.star.project.context;

/**
 * 上下文工具类，用于存储和获取当前用户信息
 */
public class BaseContext {
    
    private static final ThreadLocal<Long> threadLocal = new ThreadLocal<>();

    /**
     * 设置当前用户ID
     * @param id 用户ID
     */
    public static void setCurrentId(Long id) {
        threadLocal.set(id);
    }

    /**
     * 获取当前用户ID
     * @return 用户ID
     */
    public static Long getCurrentId() {
        return threadLocal.get();
    }

    /**
     * 清除当前用户ID
     */
    public static void removeCurrentId() {
        threadLocal.remove();
    }
}
