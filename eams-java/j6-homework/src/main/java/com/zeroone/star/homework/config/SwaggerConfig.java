package com.zeroone.star.homework.config;

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
    Docket HomeworkApi() {
        return SwaggerCore.defaultDocketBuilder(
            "作业管理模块",
            "com.zeroone.star.homework.controller",
            "homeworkmanager"
        );
    }
}
