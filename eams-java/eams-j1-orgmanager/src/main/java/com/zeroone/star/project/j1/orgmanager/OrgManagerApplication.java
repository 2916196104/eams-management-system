package com.zeroone.star.project.j1.orgmanager;

import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.mail.MailComponent;
import com.zeroone.star.project.components.pdf.PdfComponent;
import com.zeroone.star.project.components.sms.aliyun.KeyConfig;
import com.zeroone.star.project.components.sms.aliyun.SmsComponent;
import com.zeroone.star.project.config.redis.RedisConfig;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.FilterType;

@SpringBootApplication
@ComponentScan(
        basePackages = {"com.zeroone.star.project"},
        excludeFilters = @ComponentScan.Filter(
                type = FilterType.ASSIGNABLE_TYPE,
                classes = {
                        FastDfsClientComponent.class,
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
