package com.zeroone.star.project.login;

import com.zeroone.star.project.dto.login.LoginDTO;
import com.zeroone.star.project.dto.login.Oauth2TokenDTO;
import com.zeroone.star.project.dto.login.RefreshTokenDTO;
import com.zeroone.star.project.dto.login.SelfResetPasswordDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.login.LoginPageConfigVO;
import com.zeroone.star.project.vo.login.LoginVO;
import com.zeroone.star.project.vo.login.MenuTreeVO;

import java.util.List;

public interface LoginApis {

    JsonVO<LoginPageConfigVO> getLoginPageConfig(String terminalType);

    JsonVO<Oauth2TokenDTO> authLogin(LoginDTO loginDTO);

    JsonVO<Oauth2TokenDTO> refreshToken(RefreshTokenDTO refreshTokenDTO);

    JsonVO<LoginVO> getCurrUser();

    JsonVO<String> resetPassword(SelfResetPasswordDTO resetPasswordDTO);

    JsonVO<String> logout();

    JsonVO<List<MenuTreeVO>> getMenus();
}
