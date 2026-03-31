package com.zeroone.star.student;

import com.zeroone.star.student.service.IStudentFinanceService;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.cloud.openfeign.EnableFeignClients;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.FilterType;

@SpringBootApplication
@EnableDiscoveryClient
@EnableFeignClients

public class StudentApplication {
    public static void main(String[] args) {

        SpringApplication.run(StudentApplication.class, args);
    }
}
