package com.zeroone.star.login.controller;

import com.zeroone.star.project.dto.login.LoginDTO;
import com.zeroone.star.project.dto.login.Oauth2TokenDTO;
import com.zeroone.star.project.dto.login.RefreshTokenDTO;
import com.zeroone.star.project.login.LoginApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.login.LoginPageConfigVO;
import com.zeroone.star.project.vo.login.LoginVO;
import com.zeroone.star.project.vo.login.MenuTreeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * <p>
 * 描述：登录接口控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 阿伟学长
 * @version 1.0.0
 */
@RestController
@RequestMapping("/login")
@Api(tags = "登录接口")
@Validated
public class LoginController implements LoginApis {

    @GetMapping("/page-config")
    @ApiOperation(value = "获取登录页配置")
    @Override
    public JsonVO<LoginPageConfigVO> getLoginPageConfig() {
        return JsonVO.success(mockPageConfig());
    }

    @PostMapping("/auth-login")
    @ApiOperation(value = "认证登录")
    @Override
    public JsonVO<Oauth2TokenDTO> authLogin(
            @Validated @RequestBody @ApiParam(value = "登录请求参数", required = true) LoginDTO loginDTO) {
        return JsonVO.success(mockToken());
    }

    @PostMapping("/refresh-token")
    @ApiOperation(value = "刷新令牌")
    @Override
    public JsonVO<Oauth2TokenDTO> refreshToken(
            @Validated @RequestBody @ApiParam(value = "刷新令牌请求参数", required = true) RefreshTokenDTO refreshTokenDTO) {
        return JsonVO.success(mockToken());
    }

    @GetMapping("/current-user")
    @ApiOperation(value = "获取当前用户")
    @Override
    public JsonVO<LoginVO> getCurrUser() {
        return JsonVO.success(mockCurrentUser());
    }

    @GetMapping("/logout")
    @ApiOperation(value = "退出登录")
    @Override
    public JsonVO<String> logout() {
        return JsonVO.success("退出成功");
    }

    @GetMapping("/get-menus")
    @ApiOperation(value = "获取菜单")
    @Override
    public JsonVO<List<MenuTreeVO>> getMenus() {
        return JsonVO.success(mockMenus());
    }

    private LoginPageConfigVO mockPageConfig() {
        LoginPageConfigVO config = new LoginPageConfigVO();
        config.setLoginMode("account-password");
        config.setCaptchaEnabled(Boolean.TRUE);
        config.setCaptchaType("aj-captcha");
        config.setCaptchaPathPrefix("/captcha");
        return config;
    }

    private Oauth2TokenDTO mockToken() {
        Oauth2TokenDTO token = new Oauth2TokenDTO();
        token.setToken("mock-access-token");
        token.setRefreshToken("mock-refresh-token");
        token.setTokenHead("Bearer ");
        token.setExpiresIn(3600);
        return token;
    }

    private LoginVO mockCurrentUser() {
        LoginVO user = new LoginVO();
        user.setId("1");
        user.setUsername("admin");
        user.setIsEnabled((byte) 1);
        user.setRoles(Collections.singletonList("ADMIN"));
        return user;
    }

    private List<MenuTreeVO> mockMenus() {
        MenuTreeVO homeMenu = buildMenu(1, 0, "首页", "dashboard", "/dashboard");
        MenuTreeVO systemMenu = buildMenu(2, 0, "系统管理", "setting", "/system");
        MenuTreeVO userMenu = buildMenu(3, 2, "用户管理", "user", "/system/user");
        systemMenu.addChild(userMenu);
        return Arrays.asList(homeMenu, systemMenu);
    }

    private MenuTreeVO buildMenu(Integer id, Integer pid, String text, String icon, String href) {
        MenuTreeVO menu = new MenuTreeVO();
        menu.setId(id);
        menu.setPid(pid);
        menu.setText(text);
        menu.setIcon(icon);
        menu.setHref(href);
        menu.setTnId(String.valueOf(id));
        menu.setTnPid(String.valueOf(pid));
        return menu;
    }
}
