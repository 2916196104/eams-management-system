package com.zeroone.star.org.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;


@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {
    @Bean
    Docket orgApi() {
        return SwaggerCore.defaultDocketBuilder("职位数据权限管理模块", "com.zeroone.star.org.controller", "org");
    }
}

