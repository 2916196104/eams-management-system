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

/**
 * <p>
 * 描述：登录模块接口定义
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 阿伟学长
 * @version 1.0.0
 */
public interface LoginApis {
    /**
     * 获取登录页配置
     *
     * @return 登录页配置
     */
    JsonVO<LoginPageConfigVO> getLoginPageConfig();

    /**
     * 授权登录
     *
     * @param loginDTO 登录请求参数
     * @return 登录结果
     */
    JsonVO<Oauth2TokenDTO> authLogin(LoginDTO loginDTO);

    /**
     * 刷新令牌
     *
     * @param refreshTokenDTO 刷新令牌请求参数
     * @return 刷新结果
     */
    JsonVO<Oauth2TokenDTO> refreshToken(RefreshTokenDTO refreshTokenDTO);

    /**
     * 获取当前用户
     *
     * @return 当前登录用户
     */
    JsonVO<LoginVO> getCurrUser();

    JsonVO<String> resetPassword(SelfResetPasswordDTO resetPasswordDTO);

    /**
     * 退出登录
     *
     * @return 退出结果
     */
    JsonVO<String> logout();

    /**
     * 获取菜单
     *
     * @return 菜单树数据
     */
    JsonVO<List<MenuTreeVO>> getMenus();
}
