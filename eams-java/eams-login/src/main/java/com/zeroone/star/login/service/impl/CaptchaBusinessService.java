package com.zeroone.star.login.service.impl;

import cn.hutool.core.util.StrUtil;
import com.anji.captcha.model.common.ResponseModel;
import com.anji.captcha.model.vo.CaptchaVO;
import com.anji.captcha.service.CaptchaService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class CaptchaBusinessService {

    @Resource
    private CaptchaService captchaService;

    /**
     * 二次校验验证码
     * @param code
     * @return
     */
    public ResponseModel verification(String code) {
        if (StrUtil.isBlank(code)) {
            return ResponseModel.errorMsg("验证码不能为空");
        }

        CaptchaVO captchaVO = new CaptchaVO();
        captchaVO.setCaptchaVerification(code);

        try {
            // 对验证码校验
            ResponseModel response = captchaService.verification(captchaVO);
            /*  可以看到只删除了二次校验的redis数据
                String codeKey = String.format(REDIS_SECOND_CAPTCHA_KEY, captchaVO.getCaptchaVerification());
                if (!CaptchaServiceFactory.getCache(cacheType).exists(codeKey)) {
                    return ResponseModel.errorMsg(RepCodeEnum.API_CAPTCHA_INVALID);
                }

                CaptchaServiceFactory.getCache(cacheType).delete(codeKey);

                @Override
                public boolean exists(String key) {
                    return Boolean.TRUE.equals(stringRedisTemplate.hasKey(key));
                }
            */
            return response;

        } catch (Exception e) {
            return ResponseModel.errorMsg("验证码校验异常");
        }
    }


    /**
     * 根据错误码获取友好的错误信息
     */
    private String getCaptchaErrorMessage(String repCode) {
        switch (repCode) {
            case "0000":
                return "验证成功";
            case "9999":
                return "服务器内部异常";
            case "0011":
                return "参数不能为空";
            case "6110":
                return "验证码已失效，请重新获取";
            case "6111":
                return "验证失败";
            case "6112":
                return "获取验证码失败,请联系管理员";
            case "6113":
                return "底图未初始化成功，请检查路径";
            case "6201":
                return "请求次数超限，请稍后再试!";
            case "6206":
                return "无效请求，请重新获取验证码";
            case "6202":
                return "验证失败数过多，请稍后再试";
            case "6204":
                return "校验请求次数超限，请稍后再试!";
            default:
                return "验证码校验失败";
        }
    }

}
