package com.zeroone.star.sys.config;

import com.baomidou.mybatisplus.core.handlers.MetaObjectHandler;
import org.apache.ibatis.reflection.MetaObject;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

import java.time.LocalDateTime;

/**
 * @author isme
 * @description  初始化MyBatisPlus
 * @title com.zeroone.star.sys.config
 * @date 2026/3/15
 */
@Configuration
@ComponentScan("com.zeroone.star.project.config.mybatis")
public class UseMyBatisPlus {

//    填充处理器，用于填充时间
    @Bean
    public MetaObjectHandler metaObjectHandler() {
        return new MetaObjectHandler() {
            @Override
            public void insertFill(MetaObject metaObject) {
                this.strictInsertFill(metaObject, "createTime", LocalDateTime.class, LocalDateTime.now());

            }

            @Override
            public void updateFill(MetaObject metaObject) {
                this.strictInsertFill(metaObject, "updateTime", LocalDateTime.class, LocalDateTime.now());

            }
        };
    }
}
