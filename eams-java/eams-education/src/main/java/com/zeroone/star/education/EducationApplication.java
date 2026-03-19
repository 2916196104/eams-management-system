package com.zeroone.star.education;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.context.annotation.ComponentScan;

/**
 * <p>
 * 描述：程序启动入口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
// 关键代码：显式告诉 Spring 去扫描 user 组件包
@SpringBootApplication
@EnableDiscoveryClient
@MapperScan("com.zeroone.star.education.mapper")
@ComponentScan(basePackages = {"com.zeroone.star.education", "com.zeroone.star.project.components.user", "com.zeroone.star.project.components.jwt"})
public class EducationApplication {

    public static void main(String[] args) {
        SpringApplication.run(EducationApplication.class, args);
    }

}
