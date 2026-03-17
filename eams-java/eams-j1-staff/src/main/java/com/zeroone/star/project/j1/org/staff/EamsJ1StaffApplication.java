package com.zeroone.star.project.j1.org.staff;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
public class EamsJ1StaffApplication {
    public static void main(String[] args) {
        SpringApplication.run(EamsJ1StaffApplication.class, args);
    }
}