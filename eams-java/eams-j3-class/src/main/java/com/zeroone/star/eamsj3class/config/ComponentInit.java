package com.zeroone.star.eamsj3class.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

/**
 * <p>
 * 描述：导入userHolder组件
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
@Configuration
@ComponentScan({
        "com.zeroone.star.project.components.user",
        "com.zeroone.star.project.components.jwt"
})
public class ComponentInit {
}
