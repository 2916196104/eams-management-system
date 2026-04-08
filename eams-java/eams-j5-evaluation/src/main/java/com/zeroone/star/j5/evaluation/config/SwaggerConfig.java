package com.zeroone.star.j5.evaluation.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {
    @Bean
    Docket sampleApi(){

        return SwaggerCore.defaultDocketBuilder("教学评价模块","com.zeroone.star.j5.evaluation.controller","教学评价");
    }

}
