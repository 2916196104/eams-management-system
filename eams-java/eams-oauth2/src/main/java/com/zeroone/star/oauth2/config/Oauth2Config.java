package com.zeroone.star.oauth2.config;

import com.zeroone.cloud.starter.oauth2.autoconfiguration.Oauth2ServerConfig;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

/**
 * <p>
 * 描述：Oauth2配置类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Configuration
@Import(Oauth2ServerConfig.class)
public class Oauth2Config {
}
