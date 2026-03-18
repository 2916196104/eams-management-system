package com.homework.eamsj3data.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

/**
 * 数据模块的swagger
 */
@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {
    Docket SwaggerApi() {
        return SwaggerCore.defaultDocketBuilder("数据模块", "com.zeroone.star.eamsj3data", "data");
    }
}
