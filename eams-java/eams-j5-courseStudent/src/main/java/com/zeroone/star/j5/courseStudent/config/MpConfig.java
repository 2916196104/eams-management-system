package com.zeroone.star.j5.courseStudent.config;

import com.baomidou.mybatisplus.core.handlers.MetaObjectHandler;
import org.apache.ibatis.reflection.MetaObject;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

import java.time.LocalDateTime;

@Configuration
@ComponentScan("com.zeroone.star.project.config.mybatis")
public class MpConfig {

    /*
    * 创建填充处理器，用来自动填充时间
    *
    * */
    public MetaObjectHandler metaObjectHandler(){
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
