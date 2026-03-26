package com.zeroone.star.login.service.impl;

import cn.hutool.core.bean.BeanUtil;
import cn.hutool.core.convert.Convert;
import cn.hutool.core.util.StrUtil;
import com.anji.captcha.model.common.ResponseModel;
import com.zeroone.cloud.oauth2.entity.Oauth2Token;
import com.zeroone.star.login.entity.StaffDO;
import com.zeroone.star.login.exception.LoginException;
import com.zeroone.star.login.mapper.RoleMapper;
import com.zeroone.star.login.mapper.StaffMapper;
import com.zeroone.star.login.service.ILoginService;
import com.zeroone.star.login.service.IMenuService;
import com.zeroone.star.login.service.OauthService;
import com.zeroone.star.project.components.jwt.JwtComponent;
import com.zeroone.star.project.components.jwt.exception.JwtExpiredException;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.components.user.UserDTO;
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
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.RequestBody;

import javax.annotation.Resource;
import java.lang.reflect.Method;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.TimeUnit;

@Service
public class LoginServiceImpl implements ILoginService {

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
    private RoleMapper roleMapper;

    @Resource
    private PasswordEncoder passwordEncoder;

    @Resource
    private CaptchaBusinessService captchaBusinessService;

    @Value("${zo.cloud.starter.oauth2.mgr-id}")
    String clientId;
    @Value("${zo.cloud.starter.oauth2.mgr-password}")
    String clientPassword;
    @Value("${login.captcha.enabled:false}")
    Boolean captchaEnabled;

    @Autowired
    private JwtComponent jwtComponent;


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
    public JsonVO<Oauth2TokenDTO> authLogin(@Validated @RequestBody @ApiParam(value = "登录请求参数", required = true) LoginDTO loginDTO) {
        // 验证码二次校验
        if (captchaEnabled) {
            //校验LoginDTO
            if (StrUtil.isBlank(loginDTO.getCode())) {
                JsonVO.create(null, ResultStatus.FAIL.getCode(), "验证码不能为空");
            }
            //校验验证码
            ResponseModel responseModel = captchaBusinessService.verification(loginDTO.getCode());
            if (!responseModel.isSuccess()) {
                return JsonVO.create(null, Integer.parseInt(responseModel.getRepCode()), responseModel.getRepMsg());
            }
        }
        // 账号密码认证
        Map<String, String> params = new HashMap<>(5);
        params.put("grant_type", "password");
        params.put("client_id", clientId);
        params.put("client_secret", clientPassword);
        params.put("username", loginDTO.getUsername());
        params.put("password", loginDTO.getPassword());
        Oauth2Token oauth2Token = oAuthService.postAccessToken(params);

        // 认证失败
        if (oauth2Token.getErrorMsg() != null) {
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), oauth2Token.getErrorMsg());
        }

        // TODO:未实现认证成功后如何实现注销凭证（如记录凭证到内存数据库）
        Oauth2TokenDTO tokenDTO = BeanUtil.toBean(oauth2Token, Oauth2TokenDTO.class);
        //缓存token到白名单
        redisTemplate.opsForValue().set(
                RedisConstant.LOGOUT_TOKEN_PREFIX + tokenDTO.getToken(),
                RedisConstant.TOKEN_STATUS_ACTIVE,
                oauth2Token.getExpiresIn(),
                TimeUnit.SECONDS
        );

        // 响应认证成功数据
        return JsonVO.success(tokenDTO);
    }


    @Override
    public JsonVO<Oauth2TokenDTO> refreshToken(RefreshTokenDTO refreshTokenDTO) {
        // 注销凭证验证
        try {
            jwtComponent.defaultRsaVerify(refreshTokenDTO.getToken());
        }catch (Exception e){
            if (!(e instanceof JwtExpiredException))
                return JsonVO.create(null, ResultStatus.FAIL.getCode(),e.getMessage());
        }

        // 刷新凭证
        Map<String, String> params = new HashMap<>(4);
        params.put("grant_type", "refresh_token");
        params.put("client_id", clientId);
        params.put("client_secret", clientPassword);
        params.put("refresh_token", refreshTokenDTO.getRefreshToken());
        Oauth2Token oauth2Token = oAuthService.postAccessToken(params);
        // 刷新失败
        if (oauth2Token.getErrorMsg() != null) {
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), oauth2Token.getErrorMsg());
        }

        Oauth2TokenDTO tokenDTO = BeanUtil.toBean(oauth2Token, Oauth2TokenDTO.class);
        redisTemplate.opsForValue().getOperations()
                .delete(RedisConstant.LOGOUT_TOKEN_PREFIX+refreshTokenDTO.getToken());
        redisTemplate.opsForValue().set(
                RedisConstant.LOGOUT_TOKEN_PREFIX+oauth2Token.getToken()
                ,RedisConstant.TOKEN_STATUS_ACTIVE,
                oauth2Token.getExpiresIn(), TimeUnit.SECONDS);

        // 响应刷新成功数据
        return JsonVO.success(tokenDTO);
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
