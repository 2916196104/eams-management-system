package com.zeroone.star.student.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;


@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {

    @Bean
    Docket studentApi(){
        return SwaggerCore.defaultDocketBuilder("学生模块","com.zeroone.star.student.controller","student");

    }
}
