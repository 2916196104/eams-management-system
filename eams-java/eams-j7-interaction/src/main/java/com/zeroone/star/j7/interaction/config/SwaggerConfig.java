package com.zeroone.star.j7.interaction.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {

    @Bean
    Docket interactionApis() {
        return SwaggerCore.defaultDocketBuilder("zeroone-star-interaction",
                "com.zeroone.star.j7.interaction.controller",
                "interaction");
    }
}
