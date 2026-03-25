package com.zeroone.star.login.controller;

import com.zeroone.star.login.service.ILoginService;
import com.zeroone.star.project.dto.login.LoginDTO;
import com.zeroone.star.project.dto.login.Oauth2TokenDTO;
import com.zeroone.star.project.dto.login.RefreshTokenDTO;
import com.zeroone.star.project.dto.login.SelfResetPasswordDTO;
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

import javax.annotation.Resource;
import java.util.List;

/**
 * Login API controller.
 */
@RestController
@RequestMapping("/login")
@Api(tags = "登录接口")
@Validated
public class LoginController implements LoginApis {

    @Resource
    private ILoginService loginService;

    @GetMapping("/page-config")
    @ApiOperation(value = "获取登录页配置")
    @Override
    public JsonVO<LoginPageConfigVO> getLoginPageConfig() {
        return JsonVO.success(loginService.getLoginPageConfig());
    }

    @PostMapping("/auth-login")
    @ApiOperation(value = "认证登录")
    @Override
    public JsonVO<Oauth2TokenDTO> authLogin(
            @Validated @RequestBody @ApiParam(value = "登录请求参数", required = true) LoginDTO loginDTO) {
        return JsonVO.success(loginService.authLogin(loginDTO));
    }

    @PostMapping("/refresh-token")
    @ApiOperation(value = "刷新令牌")
    @Override
    public JsonVO<Oauth2TokenDTO> refreshToken(
            @Validated @RequestBody @ApiParam(value = "刷新令牌请求参数", required = true) RefreshTokenDTO refreshTokenDTO) {
        return JsonVO.success(loginService.refreshToken(refreshTokenDTO));
    }

    @GetMapping("/current-user")
    @ApiOperation(value = "获取当前用户")
    @Override
    public JsonVO<LoginVO> getCurrUser() {
        return JsonVO.success(loginService.getCurrentUser());
    }

    @PostMapping("/reset-password")
    @ApiOperation(value = "\u91cd\u7f6e\u5bc6\u7801")
    @Override
    public JsonVO<String> resetPassword(
            @Validated @RequestBody @ApiParam(value = "\u91cd\u7f6e\u5bc6\u7801\u8bf7\u6c42\u53c2\u6570", required = true) SelfResetPasswordDTO resetPasswordDTO) {
        return JsonVO.success(loginService.resetPassword(resetPasswordDTO));
    }

    @GetMapping("/logout")
    @ApiOperation(value = "退出登录")
    @Override
    public JsonVO<String> logout() {
        return JsonVO.success(loginService.logout());
    }

    @GetMapping("/get-menus")
    @ApiOperation(value = "获取菜单")
    @Override
    public JsonVO<List<MenuTreeVO>> getMenus() {
        return JsonVO.success(loginService.getMenus());
    }
}
