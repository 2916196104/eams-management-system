package com.zeroone.star.course.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

/**
 * 初始化自定义组件
 * @author yangxiao
 */
@Configuration
@ComponentScan({
        "com.zeroone.star.project.components.jwt",
        "com.zeroone.star.project.components.user"
})
public class ComponentInit {
}
