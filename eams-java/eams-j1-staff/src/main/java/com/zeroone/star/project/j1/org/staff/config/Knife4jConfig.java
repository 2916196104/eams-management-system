package com.zeroone.star.project.j1.org.staff.config;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.builders.ApiInfoBuilder;
import springfox.documentation.builders.PathSelectors;
import springfox.documentation.builders.RequestHandlerSelectors;
import springfox.documentation.spi.DocumentationType;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2;

@Configuration
@EnableSwagger2  // 启用 Swagger
public class Knife4jConfig {
    @Bean
    public Docket createRestApi() {
        return new Docket(DocumentationType.SWAGGER_2)
                .apiInfo(new ApiInfoBuilder()
                        .title("eams-j1-staff API 文档")
                        .description("员工管理模块接口文档")
                        .version("1.0")
                        .build())
                .select()
                // 扫描你的 Controller 包路径（关键！）
                .apis(RequestHandlerSelectors.basePackage("com.zeroone.star.project.j1.org.staff.controller"))
                .paths(PathSelectors.any())
                .build();
    }
}