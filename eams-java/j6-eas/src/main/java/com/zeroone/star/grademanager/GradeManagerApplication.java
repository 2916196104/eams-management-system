package com.zeroone.star.grademanager;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.cloud.openfeign.EnableFeignClients;


@SpringBootApplication
@EnableDiscoveryClient // 启用服务发现客户端，将服务注册到注册中心（如Nacos）
@EnableFeignClients    // 启用Feign客户端，支持声明式的HTTP调用其他服务
public class GradeManagerApplication {

    public static void main(String[] args) {
        SpringApplication.run(GradeManagerApplication.class, args);
    }

}
