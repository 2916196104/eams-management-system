package com.zeroone.star.gateway.service.gateway;

import com.zeroone.cloud.starter.gateway.service.TokenExtendsValidate;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 描述：这里实现注销凭证校验处理
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Service
public class TokenExtendsValidateImpl implements TokenExtendsValidate {
    @Override
    public boolean isLogout(String token) {
        // TODO：判断凭证是否注销需要在此补充逻辑
        return false;
    }
}
