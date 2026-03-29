package com.zeroone.star.project.j1.orgmanager;

import com.zeroone.star.project.components.mail.MailComponent;
import com.zeroone.star.project.components.pdf.PdfComponent;
import com.zeroone.star.project.components.sms.aliyun.KeyConfig;
import com.zeroone.star.project.components.sms.aliyun.SmsComponent;
import com.zeroone.star.project.config.redis.RedisConfig;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.FilterType;

@SpringBootApplication
@MapperScan({"com.zeroone.star.project.j1.orgmanager.mapper"})
@ComponentScan(
        basePackages = {
                "com.zeroone.star.project",
                "com.zeroone.star.project.j1.orgmanager.controller",
                "com.zeroone.star.project.j1.orgmanager.service",
                "com.zeroone.star.project.j1.orgmanager.mapstruct"
        },
        excludeFilters = @ComponentScan.Filter(
                type = FilterType.ASSIGNABLE_TYPE,
                classes = {
                        MailComponent.class,
                        PdfComponent.class,
                        RedisConfig.class,
                        KeyConfig.class,
                        SmsComponent.class
                }
        )
)
public class OrgManagerApplication {
    public static void main(String[] args) {
        SpringApplication.run(OrgManagerApplication.class, args);
    }
}
