package com.zeroone.star.login.service.impl;

import cn.hutool.core.bean.BeanUtil;
import cn.hutool.core.convert.Convert;
import cn.hutool.core.util.StrUtil;
import com.anji.captcha.model.common.ResponseModel;
import com.zeroone.cloud.oauth2.entity.Oauth2Token;
import com.zeroone.star.login.config.LoginCaptchaProperties;
import com.zeroone.star.login.entity.AppUserDO;
import com.zeroone.star.login.entity.StaffDO;
import com.zeroone.star.login.exception.LoginException;
import com.zeroone.star.login.mapper.AppUserMapper;
import com.zeroone.star.login.mapper.RoleMapper;
import com.zeroone.star.login.mapper.StaffMapper;
import com.zeroone.star.login.service.ILoginService;
import com.zeroone.star.login.service.IMenuService;
import com.zeroone.star.login.service.OauthService;
import com.zeroone.star.project.components.jwt.JwtComponent;
import com.zeroone.star.project.components.jwt.exception.JwtExpiredException;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.constant.RedisConstant;
import com.zeroone.star.project.dto.login.LoginDTO;
import com.zeroone.star.project.dto.login.Oauth2TokenDTO;
import com.zeroone.star.project.dto.login.RefreshTokenDTO;
import com.zeroone.star.project.dto.login.SelfResetPasswordDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.login.LoginPageConfigVO;
import com.zeroone.star.project.vo.login.LoginVO;
import com.zeroone.star.project.vo.login.MenuTreeVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import javax.annotation.Resource;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.TimeUnit;

@Service
public class LoginServiceImpl implements ILoginService {

    private static final String TERMINAL_MANAGER = "manager";
    private static final String TERMINAL_USER = "user";

    private static final String OAUTH_GRANT_TYPE = "grant_type";
    private static final String OAUTH_CLIENT_ID = "client_id";
    private static final String OAUTH_CLIENT_SECRET = "client_secret";
    private static final String OAUTH_USERNAME = "username";
    private static final String OAUTH_PASSWORD = "password";
    private static final String OAUTH_REFRESH_TOKEN = "refresh_token";

    @Resource
    OauthService oAuthService;
    @Resource
    UserHolder userHolder;
    @Resource
    RedisTemplate<String, Object> redisTemplate;
    @Resource
    private IMenuService menuService;
    @Resource
    private StaffMapper staffMapper;
    @Resource
    private AppUserMapper appUserMapper;
    @Resource
    private RoleMapper roleMapper;
    @Resource
    private PasswordEncoder passwordEncoder;
    @Resource
    private CaptchaBusinessService captchaBusinessService;
    @Resource
    private LoginCaptchaProperties loginCaptchaProperties;

    @Value("${zo.cloud.starter.oauth2.mgr-id}")
    String managerClientId;
    @Value("${zo.cloud.starter.oauth2.mgr-password}")
    String managerClientPassword;
    @Value("${zo.cloud.starter.oauth2.user-id}")
    String userClientId;
    @Value("${zo.cloud.starter.oauth2.user-password}")
    String userClientPassword;

    @Autowired
    private JwtComponent jwtComponent;

    @Override
    public LoginPageConfigVO getLoginPageConfig(String terminalType) {
        LoginPageConfigVO config = new LoginPageConfigVO();
        config.setLoginMode("account-password");
        config.setCaptchaEnabled(isCaptchaEnabled(terminalType));
        config.setCaptchaType("aj-captcha");
        config.setCaptchaPathPrefix("/captcha");
        return config;
    }

    @Override
    public JsonVO<Oauth2TokenDTO> authLogin(LoginDTO loginDTO) {
        String terminalType = normalizeTerminalType(loginDTO == null ? null : loginDTO.getTerminalType());
        if (isCaptchaEnabled(terminalType)) {
            if (StrUtil.isBlank(loginDTO.getCode())) {
                return JsonVO.create(null, ResultStatus.FAIL.getCode(), "\u9a8c\u8bc1\u7801\u4e0d\u80fd\u4e3a\u7a7a");
            }
            ResponseModel responseModel = captchaBusinessService.verification(loginDTO.getCode());
            if (!responseModel.isSuccess()) {
                return JsonVO.create(
                        null,
                        Convert.toInt(responseModel.getRepCode(), ResultStatus.FAIL.getCode()),
                        responseModel.getRepMsg()
                );
            }
        }

        Map<String, String> params = new HashMap<>(5);
        params.put(OAUTH_GRANT_TYPE, "password");
        params.put(OAUTH_CLIENT_ID, resolveClientId(terminalType));
        params.put(OAUTH_CLIENT_SECRET, resolveClientPassword(terminalType));
        params.put(OAUTH_USERNAME, loginDTO.getUsername());
        params.put(OAUTH_PASSWORD, loginDTO.getPassword());
        Oauth2Token oauth2Token = oAuthService.postAccessToken(params);

        if (oauth2Token.getErrorMsg() != null) {
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), oauth2Token.getErrorMsg());
        }

        Oauth2TokenDTO tokenDTO = BeanUtil.toBean(oauth2Token, Oauth2TokenDTO.class);
        cacheActiveToken(tokenDTO.getToken(), oauth2Token.getExpiresIn());
        return JsonVO.success(tokenDTO);
    }

    @Override
    public JsonVO<Oauth2TokenDTO> refreshToken(RefreshTokenDTO refreshTokenDTO) {
        try {
            jwtComponent.defaultRsaVerify(refreshTokenDTO.getToken());
        } catch (Exception e) {
            if (!(e instanceof JwtExpiredException)) {
                return JsonVO.create(null, ResultStatus.FAIL.getCode(), e.getMessage());
            }
        }

        String terminalType = normalizeTerminalType(refreshTokenDTO.getTerminalType());
        Map<String, String> params = new HashMap<>(4);
        params.put(OAUTH_GRANT_TYPE, "refresh_token");
        params.put(OAUTH_CLIENT_ID, resolveClientId(terminalType));
        params.put(OAUTH_CLIENT_SECRET, resolveClientPassword(terminalType));
        params.put(OAUTH_REFRESH_TOKEN, refreshTokenDTO.getRefreshToken());
        Oauth2Token oauth2Token = oAuthService.postAccessToken(params);
        if (oauth2Token.getErrorMsg() != null) {
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), oauth2Token.getErrorMsg());
        }

        Oauth2TokenDTO tokenDTO = BeanUtil.toBean(oauth2Token, Oauth2TokenDTO.class);
        deleteActiveToken(refreshTokenDTO.getToken());
        cacheActiveToken(oauth2Token.getToken(), oauth2Token.getExpiresIn());
        return JsonVO.success(tokenDTO);
    }

    @Override
    public LoginVO getCurrentUser() {
        UserDTO currentUser = resolveCurrentUser();
        Long userId = Convert.toLong(currentUser.getId());
        if (userId == null) {
            throw new LoginException("Current user was not found");
        }
        if (isUserTerminal(currentUser.getTerminalType())) {
            return buildAppUserLoginVO(userId);
        }
        return buildStaffLoginVO(userId);
    }

    @Override
    public String resetPassword(SelfResetPasswordDTO resetPasswordDTO) {
        UserDTO currentUser = resolveCurrentUser();
        Long userId = Convert.toLong(currentUser.getId());
        if (userId == null) {
            throw new LoginException("Current user was not found");
        }

        String encodedPassword = passwordEncoder.encode(resetPasswordDTO.getNewPassword());
        int updatedRows;
        if (isUserTerminal(currentUser.getTerminalType())) {
            AppUserDO appUser = appUserMapper.selectCurrentUserById(userId);
            if (appUser == null) {
                throw new LoginException("Current user does not exist or is disabled");
            }
            updatedRows = appUserMapper.updatePasswordByUserId(userId, encodedPassword);
        } else {
            StaffDO staff = staffMapper.selectCurrentUserById(userId);
            if (staff == null) {
                throw new LoginException("Current user does not exist or is disabled");
            }
            updatedRows = staffMapper.updatePasswordByUserId(userId, encodedPassword);
        }

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

    private LoginVO buildStaffLoginVO(Long userId) {
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

    private LoginVO buildAppUserLoginVO(Long userId) {
        AppUserDO appUser = appUserMapper.selectCurrentUserById(userId);
        if (appUser == null) {
            throw new LoginException("Current user does not exist or is disabled");
        }

        LoginVO loginVO = new LoginVO();
        loginVO.setId(String.valueOf(appUser.getId()));
        loginVO.setUsername(appUser.getMobile());
        loginVO.setName(appUser.getName());
        loginVO.setAvatar("");
        loginVO.setMobile(appUser.getMobile());
        loginVO.setIsEnabled(resolveEnabled(appUser));
        loginVO.setRoles(defaultIfNull(roleMapper.selectRoleCodesByUserId(userId)));
        loginVO.setPermissions(defaultIfNull(roleMapper.selectPermissionCodesByUserId(userId)));
        return loginVO;
    }

    private void cacheActiveToken(String token, long expiresIn) {
        if (!StringUtils.hasText(token) || redisTemplate == null) {
            return;
        }
        redisTemplate.opsForValue().set(
                RedisConstant.LOGOUT_TOKEN_PREFIX + token,
                RedisConstant.TOKEN_STATUS_ACTIVE,
                expiresIn,
                TimeUnit.SECONDS
        );
    }

    private void deleteActiveToken(String token) {
        if (!StringUtils.hasText(token) || redisTemplate == null) {
            return;
        }
        redisTemplate.delete(RedisConstant.LOGOUT_TOKEN_PREFIX + token);
    }

    private boolean isCaptchaEnabled(String terminalType) {
        return !isUserTerminal(terminalType) && Boolean.TRUE.equals(loginCaptchaProperties.getEnabled());
    }

    private boolean isUserTerminal(String terminalType) {
        return TERMINAL_USER.equals(normalizeTerminalType(terminalType));
    }

    private String normalizeTerminalType(String terminalType) {
        if (TERMINAL_USER.equalsIgnoreCase(terminalType)) {
            return TERMINAL_USER;
        }
        return TERMINAL_MANAGER;
    }

    private String resolveClientId(String terminalType) {
        return isUserTerminal(terminalType) ? userClientId : managerClientId;
    }

    private String resolveClientPassword(String terminalType) {
        return isUserTerminal(terminalType) ? userClientPassword : managerClientPassword;
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

    private Byte resolveEnabled(AppUserDO appUser) {
        if (appUser.getState() != null) {
            return appUser.getState();
        }
        return 1;
    }

    private List<String> defaultIfNull(List<String> values) {
        return values == null ? Collections.emptyList() : values;
    }

    private Long resolveCurrentUserId() {
        UserDTO currentUser = resolveCurrentUser();
        return currentUser == null ? null : Convert.toLong(currentUser.getId());
    }

    private UserDTO resolveCurrentUser() {
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            if (currentUser == null) {
                throw new LoginException("Current user was not found");
            }
            if (!StringUtils.hasText(currentUser.getTerminalType())) {
                currentUser.setTerminalType(TERMINAL_MANAGER);
            }
            return currentUser;
        } catch (LoginException exception) {
            throw exception;
        } catch (Exception e) {
            throw new LoginException("Current user was not found");
        }
    }
}
