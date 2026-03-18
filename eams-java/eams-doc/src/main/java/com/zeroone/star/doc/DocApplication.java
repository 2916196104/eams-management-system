package com.zeroone.star.doc;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;

// 核心：排除数据源自动配置，让服务跳过数据库配置直接启动
@SpringBootApplication(exclude = DataSourceAutoConfiguration.class)
public class DocApplication {
    public static void main(String[] args) {
        SpringApplication.run(DocApplication.class, args);
    }
}