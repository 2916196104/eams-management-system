package com.zeroone.star.eas;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.cloud.openfeign.EnableFeignClients;


@SpringBootApplication
@EnableDiscoveryClient // 启用服务发现客户端，将服务注册到注册中心（如Nacos）

public class GradeManagerApplication {

    public static void main(String[] args) {
        SpringApplication.run(GradeManagerApplication.class, args);
    }

}
