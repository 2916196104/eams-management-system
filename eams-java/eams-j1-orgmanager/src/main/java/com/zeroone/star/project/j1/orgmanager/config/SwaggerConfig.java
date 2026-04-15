package com.zeroone.star.project.j1.orgmanager.config;

import com.zeroone.star.project.config.swagger.SwaggerCore;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

/**
 * <p>
 * 描述：职位管理接口文档配置
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@Configuration
@EnableSwagger2WebMvc
public class SwaggerConfig {
    @Bean
    public Docket orgManagerApi() {
        return SwaggerCore.defaultDocketBuilder(
                "组织页面",
                "com.zeroone.star.project.j1.orgmanager.controller",
                "j1-orgmanager"
        );
    }
}
