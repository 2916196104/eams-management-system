package com.zeroone.star.finance.config;

import com.zeroone.star.project.components.jwt.JwtComponent;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

/**
 * Swagger配置类
 */
@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {
    @Bean
    Docket gradeManagerApi() {
        return SwaggerCore.defaultDocketBuilder(
            "财务管理模块",
            "com.zeroone.star.finance.controller",

            "finance"
        );
    }

    @Bean
    public JwtComponent jwtComponent() {
        return new JwtComponent(); // 创建JwtComponent实例并交给Spring管理
    }

    @Bean
    public UserHolder userHolder() {
        return new UserHolder();
    }
}
