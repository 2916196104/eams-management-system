package com.zeroone.star.j5.courseschedule.config;

import com.baomidou.mybatisplus.extension.plugins.MybatisPlusInterceptor;
import com.baomidou.mybatisplus.extension.plugins.inner.PaginationInnerInterceptor;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class MybatisPlusConfig {
    @Bean
    public MybatisPlusInterceptor mybatisPlusInterceptor(){
        MybatisPlusInterceptor myInterceptor = new MybatisPlusInterceptor();
        myInterceptor.addInnerInterceptor(new PaginationInnerInterceptor());
        return myInterceptor;
    }
}