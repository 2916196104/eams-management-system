package com.zeroone.star.eamsj3supplies.config;

import com.baomidou.mybatisplus.core.handlers.MetaObjectHandler;
import org.apache.ibatis.reflection.MetaObject;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

import java.time.LocalDateTime;

@Configuration
@ComponentScan("com.zeroone.star.project.config.mybatis")

public class UseMybatisPlus {

    @Bean
    public MetaObjectHandler metaObjectHandler(){
        return new MetaObjectHandler(){
            @Override
            public void insertFill(MetaObject metaObject) {

                this.strictInsertFill(metaObject,"creattime", LocalDateTime.class,LocalDateTime.now());
            }

            @Override
            public void updateFill(MetaObject metaObject) {
                this.strictUpdateFill(metaObject, "updatetime", LocalDateTime.class, LocalDateTime.now());
            }
        };
    }

}
