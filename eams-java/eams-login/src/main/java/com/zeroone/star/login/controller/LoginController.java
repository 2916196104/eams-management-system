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
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.List;

@RestController
@RequestMapping("/login")
@Api(tags = "\u767b\u5f55\u63a5\u53e3")
@Validated
public class LoginController implements LoginApis {

    @Resource
    private ILoginService loginService;

    @GetMapping("/page-config")
    @ApiOperation(value = "\u83b7\u53d6\u767b\u5f55\u9875\u914d\u7f6e")
    @Override
    public JsonVO<LoginPageConfigVO> getLoginPageConfig(
            @RequestParam(value = "terminalType", required = false) String terminalType) {
        return JsonVO.success(loginService.getLoginPageConfig(terminalType));
    }

    @PostMapping("/auth-login")
    @ApiOperation(value = "\u8ba4\u8bc1\u767b\u5f55")
    @Override
    public JsonVO<Oauth2TokenDTO> authLogin(
            @Validated @RequestBody @ApiParam(value = "\u767b\u5f55\u8bf7\u6c42\u53c2\u6570", required = true) LoginDTO loginDTO) {
        return loginService.authLogin(loginDTO);
    }

    @PostMapping("/refresh-token")
    @ApiOperation(value = "\u5237\u65b0\u4ee4\u724c")
    @Override
    public JsonVO<Oauth2TokenDTO> refreshToken(
            @Validated @RequestBody @ApiParam(value = "\u5237\u65b0\u4ee4\u724c\u8bf7\u6c42\u53c2\u6570", required = true) RefreshTokenDTO refreshTokenDTO) {
        return loginService.refreshToken(refreshTokenDTO);
    }

    @GetMapping("/current-user")
    @ApiOperation(value = "\u83b7\u53d6\u5f53\u524d\u7528\u6237")
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
    @ApiOperation(value = "\u9000\u51fa\u767b\u5f55")
    @Override
    public JsonVO<String> logout() {
        return JsonVO.success(loginService.logout());
    }

    @GetMapping("/get-menus")
    @ApiOperation(value = "\u83b7\u53d6\u83dc\u5355")
    @Override
    public JsonVO<List<MenuTreeVO>> getMenus() {
        return JsonVO.success(loginService.getMenus());
    }
}
