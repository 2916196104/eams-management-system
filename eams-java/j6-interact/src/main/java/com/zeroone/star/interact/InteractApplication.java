package com.zeroone.star.interact;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.cloud.openfeign.EnableFeignClients;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@EnableDiscoveryClient
@EnableFeignClients
@MapperScan("com.zeroone.star.interact.mapper")
@ComponentScan(basePackages = {
        "com.zeroone.star.interact", // 当前模块自己的包 (必须保留，否则 Controller/Service 扫不到)
        "com.zeroone.star.project.config.mybatis" // 专门为了加载 MP 配置而添加的包
})
public class InteractApplication {

    public static void main(String[] args) {
        SpringApplication.run(InteractApplication.class, args);
    }

}
