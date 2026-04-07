package com.zeroone.star.login.config;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.cloud.context.config.annotation.RefreshScope;
import org.springframework.stereotype.Component;

/**
 * Centralized captcha config so login endpoints read the same refreshable value.
 */
@Data
@Component
@RefreshScope
@ConfigurationProperties(prefix = "login.captcha")
public class LoginCaptchaProperties {

    /**
     * Whether captcha is required for account-password login.
     */
    private Boolean enabled = false;
}
