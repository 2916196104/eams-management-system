package com.zeroone.star.login.controller;

import cn.hutool.core.bean.BeanUtil;
import com.zeroone.cloud.oauth2.entity.Oauth2Token;
import com.zeroone.star.login.service.IMenuService;
import com.zeroone.star.login.service.OauthService;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.login.LoginDTO;
import com.zeroone.star.project.dto.login.Oauth2TokenDTO;
import com.zeroone.star.project.dto.login.RefreshTokenDTO;
import com.zeroone.star.project.login.LoginApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.login.LoginVO;
import com.zeroone.star.project.vo.login.MenuTreeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * <p>
 * 描述：登录接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@RestController
@RequestMapping("login")
@Api(tags = "login")
public class LoginController implements LoginApis {
    @Resource
    OauthService oAuthService;
    @Resource
    UserHolder userHolder;
    @Value("${zo.cloud.starter.oauth2.mgr-id}")
    String clientId;
    @Value("${zo.cloud.starter.oauth2.mgr-password}")
    String clientPassword;

    @ApiOperation(value = "授权登录")
    @PostMapping("auth-login")
    @Override
    public JsonVO<Oauth2TokenDTO> authLogin(LoginDTO loginDTO) {
        // TODO:未实现验证码验证,注意：接入验证码后需要加一个启动或关闭验证码验证功能的开关，此开关可以在Nacos配置中心中动态的调整

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

        // 响应认证成功数据
        return JsonVO.success(BeanUtil.toBean(oauth2Token, Oauth2TokenDTO.class));
    }

    @ApiOperation(value = "刷新登录")
    @PostMapping("refresh-token")
    @Override
    public JsonVO<Oauth2TokenDTO> refreshToken(RefreshTokenDTO refreshTokenDTO) {
        // TODO:未实现注销凭证验证

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

        // TODO:未实现刷新成功后如何刷新注销凭证（如删除与更新内存数据库）

        // 响应刷新成功数据
        return JsonVO.success(BeanUtil.toBean(oauth2Token, Oauth2TokenDTO.class));
    }

    @ApiOperation(value = "获取当前用户")
    @GetMapping("current-user")
    @Override
    public JsonVO<LoginVO> getCurrUser() {
        UserDTO currentUser;
        try {
            currentUser = userHolder.getCurrentUser();
        } catch (Exception e) {
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), e.getMessage());
        }
        if (currentUser == null) {
            return JsonVO.fail(null);
        } else {
            // TODO:这里需要根据业务需求，重新实现
            LoginVO vo = new LoginVO();
            BeanUtil.copyProperties(currentUser, vo);
            return JsonVO.success(vo);
        }
    }

    @ApiOperation(value = "退出登录")
    @GetMapping("logout")
    @Override
    public JsonVO<String> logout() {
        // 获取当前请求的token
        String token = userHolder.getCurrentToken();
        if (token != null){
            // TODO:登出逻辑，需要配合登录逻辑实现
            return JsonVO.success("退出成功");
        }
        return JsonVO.fail("获取凭证失败，退出失败");
    }

    @Resource
    IMenuService menuService;

    @ApiOperation(value = "获取菜单")
    @GetMapping("get-menus")
    @Override
    public JsonVO<List<MenuTreeVO>> getMenus() throws Exception {
        // TODO:未实现根据实际数据库设计业务逻辑，下面逻辑属于示例逻辑
        // 1 获取当前用户
        UserDTO currentUser = userHolder.getCurrentUser();
        // 2 获取当前用户拥有的菜单
        List<MenuTreeVO> menus = menuService.listMenuByRoleName(currentUser.getRoles());
        return JsonVO.success(menus);
    }
}
