package com.zeroone.star.project.components.user;

import cn.hutool.core.convert.Convert;
import cn.hutool.json.JSONObject;
import com.zeroone.star.project.components.jwt.JwtComponent;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;
import org.yaml.snakeyaml.util.UriEncoder;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;

/**
 * <p>
 * 描述：获取登录用户信息
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Component
public class UserHolder {

    private static final String TERMINAL_MANAGER = "manager";
    private static final String TERMINAL_USER = "user";
    private static final String MANAGER_CLIENT_ID = "eams-manager";
    private static final String USER_CLIENT_ID = "eams-app";

    @Resource
    JwtComponent jwtComponent;

    /**
     * 从请求头中获取用户信息
     * @return 用户信息
     * @throws Exception 解析失败抛出异常
     */
    @SuppressWarnings("MismatchedQueryAndUpdateOfCollection")
    public UserDTO getCurrentUser() throws Exception {
        ServletRequestAttributes servletRequestAttributes =
                (ServletRequestAttributes) RequestContextHolder.getRequestAttributes();
        if (servletRequestAttributes == null) {
            return null;
        }

        HttpServletRequest request = servletRequestAttributes.getRequest();
        String userStr = request.getHeader("user");
        if (userStr == null) {
            String authorization = request.getHeader("Authorization");
            if (!StringUtils.hasText(authorization)) {
                return null;
            }
            String realToken = authorization.replace("Bearer ", "");
            userStr = jwtComponent.defaultRsaVerify(realToken);
        } else {
            userStr = UriEncoder.decode(userStr);
        }

        JSONObject userJsonObject = new JSONObject(userStr);
        return UserDTO.builder()
                .id(Convert.toStr(userJsonObject.get("id")))
                .username(userJsonObject.getStr("user_name"))
                .isEnabled(Convert.toByte(1))
                .roles(Convert.toList(String.class, userJsonObject.get("authorities")))
                .orgId(Convert.toLong(userJsonObject.get("org_id")))
                .terminalType(resolveTerminalType(userJsonObject))
                .build();
    }

    /**
     * 从请求头中获取当前请求的token
     * @return 没有获取到返回null
     */
    public String getCurrentToken() {
        ServletRequestAttributes servletRequestAttributes =
                (ServletRequestAttributes) RequestContextHolder.getRequestAttributes();
        if (servletRequestAttributes == null) {
            return null;
        }
        HttpServletRequest request = servletRequestAttributes.getRequest();
        String token = request.getHeader("Authorization");
        if (!StringUtils.hasText(token)) {
            return null;
        }
        return token.replace("Bearer ", "");
    }

    private String resolveTerminalType(JSONObject userJsonObject) {
        String terminalType = userJsonObject.getStr("terminal_type");
        if (StringUtils.hasText(terminalType)) {
            return terminalType;
        }

        String clientId = userJsonObject.getStr("client_id");
        if (USER_CLIENT_ID.equals(clientId)) {
            return TERMINAL_USER;
        }
        if (MANAGER_CLIENT_ID.equals(clientId)) {
            return TERMINAL_MANAGER;
        }
        return TERMINAL_MANAGER;
    }
}
