package com.zeroone.star.oauth2.service.impl.oauth2;

import com.zeroone.cloud.oauth2.entity.SecurityUser;
import com.zeroone.cloud.starter.oauth2.service.LoadUserDetailService;
import com.zeroone.star.oauth2.entity.Role;
import com.zeroone.star.oauth2.entity.User;
import com.zeroone.star.oauth2.service.IRoleService;
import com.zeroone.star.oauth2.service.IUserService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class LoadUserDetailServiceImpl implements LoadUserDetailService {

    private static final String TERMINAL_MANAGER = "manager";
    private static final String TERMINAL_USER = "user";

    @Resource
    private IUserService userService;

    @Resource
    private IRoleService roleService;

    @Override
    public SecurityUser loadUserDetailForMgr(String username) throws UsernameNotFoundException {
        User user = userService.getManagerByMobile(username);
        if (user == null) {
            throw new UsernameNotFoundException("\u7528\u6237\u540d\u6216\u5bc6\u7801\u9519\u8bef");
        }
        user.setTerminalType(TERMINAL_MANAGER);
        return buildSecurityUser(user);
    }

    @Override
    public SecurityUser loadUserDetailForUser(String username) throws UsernameNotFoundException {
        User user = userService.getUserByMobile(username);
        if (user == null) {
            throw new UsernameNotFoundException("\u7528\u6237\u540d\u6216\u5bc6\u7801\u9519\u8bef");
        }
        user.setTerminalType(TERMINAL_USER);
        return buildSecurityUser(user);
    }

    private SecurityUser buildSecurityUser(User user) {
        List<Role> roles = roleService.listRoleByUserId(user.getId());
        if (roles == null) {
            roles = Collections.emptyList();
        }
        return SecurityUser.create(
                user,
                user.getUsername(),
                user.getPassword(),
                roles.stream().map(Role::getKeyword).collect(Collectors.toList())
        );
    }
}
