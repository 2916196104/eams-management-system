package com.zeroone.star.org;

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
public class OrgManagerApplication {
    public static void main(String[] args) {
        SpringApplication.run(OrgManagerApplication.class, args);
    }
}
