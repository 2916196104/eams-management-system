package com.zeroone.star.eamsj3data.config;


import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {
    @Bean
    Docket SwaggerApi(){
        return SwaggerCore.defaultDocketBuilder("学评教课时统计","com.zeroone.star.eamsj3data.controller","data");
    }
}
