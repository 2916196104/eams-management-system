package com.zeroone.star.sys.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

/**
 * @author isme
 * @description   Swagger配置类
 * @title com.zeroone.star.sys.config
 * @date 2026/3/15
 */
@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {
    @Bean
    Docket sysApi(){
        return SwaggerCore.defaultDocketBuilder("系统模块", "com.zeroone.star.sys.controller", "sys");
    }
}
