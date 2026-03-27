package com.zeroone.star.oauth2.service.impl.oauth2;

import com.zeroone.cloud.oauth2.entity.SecurityUser;
import com.zeroone.cloud.starter.oauth2.service.JwtTokenEnhancerDataService;
import com.zeroone.star.oauth2.entity.User;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.Map;

/**
 * <p>
 * 描述：Jwt Token增强数据处理服务实现
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Service
public class JwtTokenEnhancerDataServiceImpl implements JwtTokenEnhancerDataService {
    @Override
    public Map<String, Object> enhance(SecurityUser securityUser) {
        User user = (User) securityUser.getExtendsObject();
        Map<String, Object> info = new HashMap<>(4);
        info.put("id", user.getId());
        info.put("org_id", user.getOrgId());
        info.put("name", user.getName());
        return info;
    }
}
