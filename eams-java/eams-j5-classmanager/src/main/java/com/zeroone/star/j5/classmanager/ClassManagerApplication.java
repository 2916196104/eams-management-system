package com.zeroone.star.j5.classmanager;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;

@SpringBootApplication
@EnableDiscoveryClient
public class ClassManagerApplication {
    public static void main(String[] args) {

        SpringApplication.run(ClassManagerApplication.class, args);
    }
}
