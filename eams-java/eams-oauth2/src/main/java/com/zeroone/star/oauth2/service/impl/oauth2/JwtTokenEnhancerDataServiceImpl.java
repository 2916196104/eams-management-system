package com.zeroone.star.oauth2.service.impl.oauth2;

import com.zeroone.cloud.oauth2.entity.SecurityUser;
import com.zeroone.cloud.starter.oauth2.service.JwtTokenEnhancerDataService;
import com.zeroone.star.oauth2.entity.User;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.Map;

@Service
public class JwtTokenEnhancerDataServiceImpl implements JwtTokenEnhancerDataService {

    @Override
    public Map<String, Object> enhance(SecurityUser securityUser) {
        Map<String, Object> info = new HashMap<>(4);
        if (!(securityUser.getExtendsObject() instanceof User)) {
            return info;
        }

        User user = (User) securityUser.getExtendsObject();
        info.put("id", user.getId());
        info.put("org_id", user.getOrgId());
        info.put("name", user.getName());
        info.put("terminal_type", user.getTerminalType());
        return info;
    }
}
