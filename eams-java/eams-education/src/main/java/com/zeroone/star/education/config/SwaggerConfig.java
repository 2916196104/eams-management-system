package com.zeroone.star.education.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import io.swagger.models.Swagger;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

/*
* Swagger配置类
* */
@EnableSwagger2WebMvc
@Configuration
public class SwaggerConfig {
    @Bean
    Docket educationApi(){
        return SwaggerCore.defaultDocketBuilder("教务模块", "com.zeroone.star.education.controller", "education");
    }
}
