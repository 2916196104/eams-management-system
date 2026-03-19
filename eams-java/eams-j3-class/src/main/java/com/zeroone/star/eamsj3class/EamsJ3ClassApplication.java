package com.zeroone.star.eamsj3class;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;

@SpringBootApplication
@EnableDiscoveryClient
public class EamsJ3ClassApplication {

    public static void main(String[] args) {
        SpringApplication.run(EamsJ3ClassApplication.class, args);
    }

}
