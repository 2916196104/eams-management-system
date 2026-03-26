package com.zeroone.star.j5.classmanager.config;

import com.baomidou.mybatisplus.annotation.DbType;
import com.baomidou.mybatisplus.core.handlers.MetaObjectHandler;
import com.baomidou.mybatisplus.extension.plugins.MybatisPlusInterceptor;
import com.baomidou.mybatisplus.extension.plugins.inner.PaginationInnerInterceptor;
import org.apache.ibatis.reflection.MetaObject;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Component;

import java.time.LocalDateTime;

@Configuration
@Component("com.zeroone.star.project.config.mybatis")
public class UserMybatisPlusConfig {
    @Bean
    public MetaObjectHandler metaObjectHandler (){
         return new MetaObjectHandler() {
             @Override
             public void insertFill(MetaObject metaObject) {
                 this.strictInsertFill(metaObject,"createTime", LocalDateTime.class,LocalDateTime.now());
             }

             @Override
             public void updateFill(MetaObject metaObject) {
                 this.strictInsertFill(metaObject,"createTime", LocalDateTime.class,LocalDateTime.now());

             }
         };
    }
    @Bean
    public MybatisPlusInterceptor mybatisPlusInterceptor() {
        MybatisPlusInterceptor interceptor = new MybatisPlusInterceptor();
        interceptor.addInnerInterceptor(new PaginationInnerInterceptor(DbType.MYSQL));
        return interceptor;
    }


}
