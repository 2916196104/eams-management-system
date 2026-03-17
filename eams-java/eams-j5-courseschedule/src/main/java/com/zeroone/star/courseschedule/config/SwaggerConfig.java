package com.zeroone.star.courseschedule.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {
    @Bean
    Docket projectApi(){
        return SwaggerCore.defaultDocketBuilder("项目名称","com.zeroone.star.courseschedule.controller","分组");
    }

}
