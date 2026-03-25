package com.zeroone.star.eamsj3system;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan("com.zeroone.star.eamsj3system.mapper")
public class EamsJ3SystemApplication {

    public static void main(String[] args) {
        SpringApplication.run(EamsJ3SystemApplication.class, args);
    }

}
