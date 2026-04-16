package com.zeroone.star.eas.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {

    @Bean
    public Docket financeApi() {
        return SwaggerCore.defaultDocketBuilder(
            "年级管理模块",
            "com.zeroone.star.eas.controller",
            "grademanager"
        );
    }
}