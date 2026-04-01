package com.zeroone.star.interact;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.cloud.openfeign.EnableFeignClients;
import org.springframework.context.annotation.ComponentScan;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

@SpringBootApplication
@EnableDiscoveryClient
@EnableSwagger2WebMvc
@EnableFeignClients
@MapperScan("com.zeroone.star.interact.mapper")
@ComponentScan(basePackages = {
        "com.zeroone.star.interact",
        "com.zeroone.star.project.config.mybatis",
        "com.zeroone.star.project.components.fastdfs"
})
public class InteractApplication {

    public static void main(String[] args) {
        SpringApplication.run(InteractApplication.class, args);
    }

}
