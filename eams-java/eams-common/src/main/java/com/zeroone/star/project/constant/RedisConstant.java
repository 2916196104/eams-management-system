package com.zeroone.star.project.constant;

/**
 * <p>
 * 描述：Redis相关常量
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
public interface RedisConstant {
    /**
     * 角色资源映射Map的key
     */
    String RESOURCE_ROLES_MAP = "AUTH:RESOURCE_ROLES";
    /**
     * 登出token前缀
     */
    String LOGOUT_TOKEN_PREFIX  = "LOGOUT_TOKEN:";

    /**
     * token状态：活跃
     */
    String TOKEN_STATUS_ACTIVE = "ACTIVE";
}
