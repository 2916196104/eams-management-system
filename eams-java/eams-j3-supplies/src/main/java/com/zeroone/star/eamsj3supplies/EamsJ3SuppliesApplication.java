package com.zeroone.star.eamsj3supplies;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan("com.zeroone.star.eamsj3supplies.mapper")
public class EamsJ3SuppliesApplication {

    public static void main(String[] args) {
        SpringApplication.run(EamsJ3SuppliesApplication.class, args);
    }

}
