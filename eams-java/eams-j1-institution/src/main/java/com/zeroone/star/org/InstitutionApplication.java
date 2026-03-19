package com.zeroone.star.org;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;


@SpringBootApplication
@EnableDiscoveryClient
public class InstitutionApplication {
    public static void main(String[] args) {
        SpringApplication.run(InstitutionApplication.class, args);
    }
}