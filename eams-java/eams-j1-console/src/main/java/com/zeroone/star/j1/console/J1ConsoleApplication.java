package com.zeroone.star.j1.console;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;

/**
 * <p>
 * 描述：J1控制台服务启动类
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@SpringBootApplication
@EnableDiscoveryClient
public class J1ConsoleApplication {
    public static void main(String[] args) {
        SpringApplication.run(J1ConsoleApplication.class, args);
    }
}
