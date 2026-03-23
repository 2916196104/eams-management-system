package com.zeroone.star.org;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@EnableDiscoveryClient
@MapperScan("com.zeroone.star.org.mapper")
@ComponentScan(basePackages = {
        "com.zeroone.star.org",
        "com.zeroone.star.project.components.jwt",
        "com.zeroone.star.project.components.user",
        "com.zeroone.star.project.config"})
public class InstitutionApplication {
    public static void main(String[] args) {
        SpringApplication.run(InstitutionApplication.class, args);
    }
}
