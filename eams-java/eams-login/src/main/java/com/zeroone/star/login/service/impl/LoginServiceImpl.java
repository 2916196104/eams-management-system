package com.zeroone.star.login.service.impl;

import cn.hutool.core.convert.Convert;
import com.anji.captcha.model.common.ResponseModel;
import com.zeroone.cloud.oauth2.entity.Oauth2Token;
import com.zeroone.star.login.entity.StaffDO;
import com.zeroone.star.login.exception.LoginException;
import com.zeroone.star.login.mapper.RoleMapper;
import com.zeroone.star.login.mapper.StaffMapper;
import com.zeroone.star.login.service.ILoginService;
import com.zeroone.star.login.service.IMenuService;
import com.zeroone.star.login.service.OauthService;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.dto.login.LoginDTO;
import com.zeroone.star.project.dto.login.Oauth2TokenDTO;
import com.zeroone.star.project.dto.login.RefreshTokenDTO;
import com.zeroone.star.project.dto.login.SelfResetPasswordDTO;
import com.zeroone.star.project.vo.login.LoginPageConfigVO;
import com.zeroone.star.project.vo.login.LoginVO;
import com.zeroone.star.project.vo.login.MenuTreeVO;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import javax.annotation.Resource;
import java.lang.reflect.Method;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Service
public class LoginServiceImpl implements ILoginService {

    private static final String OAUTH_GRANT_TYPE = "grant_type";
    private static final String OAUTH_CLIENT_ID = "client_id";
    private static final String OAUTH_CLIENT_SECRET = "client_secret";
    private static final String OAUTH_USERNAME = "username";
    private static final String OAUTH_PASSWORD = "password";
    private static final String OAUTH_REFRESH_TOKEN = "refresh_token";

    @Resource
    private OauthService oauthService;

    @Resource
    private UserHolder userHolder;

    @Resource
    private CaptchaBusinessService captchaBusinessService;

    @Resource
    private IMenuService menuService;

    @Resource
    private StaffMapper staffMapper;

    @Resource
    private RoleMapper roleMapper;

    @Resource
    private PasswordEncoder passwordEncoder;

    @Value("${zo.cloud.starter.oauth2.mgr-id}")
    private String clientId;

    @Value("${zo.cloud.starter.oauth2.mgr-password}")
    private String clientPassword;

    @Override
    public LoginPageConfigVO getLoginPageConfig() {
        LoginPageConfigVO config = new LoginPageConfigVO();
        config.setLoginMode("account-password");
        config.setCaptchaEnabled(Boolean.TRUE);
        config.setCaptchaType("aj-captcha");
        config.setCaptchaPathPrefix("/captcha");
        return config;
    }

    @Override
    public Oauth2TokenDTO authLogin(LoginDTO loginDTO) {
        validateCaptcha(loginDTO.getCode());
        Map<String, String> params = new HashMap<>(5);
        params.put(OAUTH_GRANT_TYPE, OAUTH_PASSWORD);
        params.put(OAUTH_CLIENT_ID, clientId);
        params.put(OAUTH_CLIENT_SECRET, clientPassword);
        params.put(OAUTH_USERNAME, loginDTO.getUsername());
        params.put(OAUTH_PASSWORD, loginDTO.getPassword());
        return requestToken(params);
    }

    @Override
    public Oauth2TokenDTO refreshToken(RefreshTokenDTO refreshTokenDTO) {
        Map<String, String> params = new HashMap<>(4);
        params.put(OAUTH_GRANT_TYPE, OAUTH_REFRESH_TOKEN);
        params.put(OAUTH_CLIENT_ID, clientId);
        params.put(OAUTH_CLIENT_SECRET, clientPassword);
        params.put(OAUTH_REFRESH_TOKEN, refreshTokenDTO.getRefreshToken());
        return requestToken(params);
    }

    @Override
    public LoginVO getCurrentUser() {
        Long userId = resolveCurrentUserId();
        if (userId == null) {
            throw new LoginException("Current user was not found");
        }

        StaffDO staff = staffMapper.selectCurrentUserById(userId);
        if (staff == null) {
            throw new LoginException("Current user does not exist or is disabled");
        }

        LoginVO loginVO = new LoginVO();
        loginVO.setId(String.valueOf(staff.getId()));
        loginVO.setUsername(staff.getMobile());
        loginVO.setName(staff.getName());
        loginVO.setAvatar(StringUtils.hasText(staff.getHeadImg()) ? staff.getHeadImg() : "");
        loginVO.setMobile(staff.getMobile());
        loginVO.setIsEnabled(resolveEnabled(staff));
        loginVO.setRoles(defaultIfNull(roleMapper.selectRoleCodesByUserId(userId)));
        loginVO.setPermissions(defaultIfNull(roleMapper.selectPermissionCodesByUserId(userId)));
        return loginVO;
    }

    @Override
    public String resetPassword(SelfResetPasswordDTO resetPasswordDTO) {
        Long userId = resolveCurrentUserId();
        if (userId == null) {
            throw new LoginException("Current user was not found");
        }

        StaffDO staff = staffMapper.selectCurrentUserById(userId);
        if (staff == null) {
            throw new LoginException("Current user does not exist or is disabled");
        }

        String encodedPassword = passwordEncoder.encode(resetPasswordDTO.getNewPassword());
        int updatedRows = staffMapper.updatePasswordByUserId(userId, encodedPassword);
        if (updatedRows != 1) {
            throw new LoginException("Password reset failed");
        }

        return "\u5bc6\u7801\u4fee\u6539\u6210\u529f\uff0c\u8bf7\u91cd\u65b0\u767b\u5f55";
    }

    @Override
    public String logout() {
        return "Logout success";
    }

    @Override
    public List<MenuTreeVO> getMenus() {
        Long userId = resolveCurrentUserId();
        if (userId == null) {
            throw new LoginException("Current user was not found");
        }
        List<String> roleCodes = roleMapper.selectRoleCodesByUserId(userId);
        if (roleCodes == null || roleCodes.isEmpty()) {
            throw new LoginException("Current user has no roles");
        }
        return menuService.listMenuByRoleName(roleCodes);
    }

    private void validateCaptcha(String code) {
        ResponseModel response = captchaBusinessService.verification(code);
        if (response == null) {
            throw new LoginException("Captcha validation failed");
        }

        Object successValue = invokeGetter(response, "isSuccess");
        if (successValue == null) {
            successValue = invokeGetter(response, "getSuccess");
        }
        if (successValue instanceof Boolean && (Boolean) successValue) {
            return;
        }

        Object repCode = invokeGetter(response, "getRepCode");
        if ("0000".equals(String.valueOf(repCode))) {
            return;
        }

        Object message = invokeGetter(response, "getRepMsg");
        if (message == null) {
            message = invokeGetter(response, "getMessage");
        }
        throw new LoginException(message == null ? "Captcha validation failed" : String.valueOf(message));
    }

    private Object invokeGetter(Object target, String methodName) {
        try {
            Method method = target.getClass().getMethod(methodName);
            return method.invoke(target);
        } catch (Exception ignored) {
            return null;
        }
    }

    private Oauth2TokenDTO requestToken(Map<String, String> params) {
        Oauth2Token oauth2Token = oauthService.postAccessToken(params);
        if (oauth2Token == null) {
            throw new LoginException("Authentication service did not respond");
        }
        if (StringUtils.hasText(oauth2Token.getErrorMsg())) {
            throw new LoginException(oauth2Token.getErrorMsg());
        }

        Oauth2TokenDTO tokenDTO = new Oauth2TokenDTO();
        tokenDTO.setToken(oauth2Token.getToken());
        tokenDTO.setRefreshToken(oauth2Token.getRefreshToken());
        tokenDTO.setTokenHead(oauth2Token.getTokenHead());
        tokenDTO.setExpiresIn(oauth2Token.getExpiresIn());
        tokenDTO.setClientId(oauth2Token.getClientId());
        return tokenDTO;
    }

    private Byte resolveEnabled(StaffDO staff) {
        if (staff.getDeleted() != null && staff.getDeleted() == 1) {
            return 0;
        }
        if (staff.getState() != null) {
            return staff.getState();
        }
        return 1;
    }

    private List<String> defaultIfNull(List<String> values) {
        return values == null ? Collections.emptyList() : values;
    }

    private Long resolveCurrentUserId() {
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            return currentUser == null ? null : Convert.toLong(currentUser.getId());
        } catch (Exception e) {
            throw new LoginException("Current user was not found");
        }
    }
}
