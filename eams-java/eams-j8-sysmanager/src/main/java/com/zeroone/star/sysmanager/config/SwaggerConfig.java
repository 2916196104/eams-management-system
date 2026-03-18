package com.zeroone.star.sysmanager.config;

import com.github.xiaoymin.knife4j.spring.annotations.EnableKnife4j;
import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2;

@Configuration
@EnableSwagger2
@EnableKnife4j
public class SwaggerConfig {
    @Bean
    Docket sysmanagerApi() {
        return SwaggerCore.defaultDocketBuilder("系统模块", "com.zeroone.star.sysmanager.controller", "sysmanager");
    }
}