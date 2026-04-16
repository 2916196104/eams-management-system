package com.zeroone.star.material.config;

import com.baomidou.mybatisplus.core.handlers.MetaObjectHandler;
import com.zeroone.star.project.components.user.UserHolder;
import org.apache.ibatis.reflection.MetaObject;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

import javax.annotation.Resource;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：初始化MyBatisPlus
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Configuration
@ComponentScan("com.zeroone.star.project.config.mybatis")
public class UseMyBaitsPlus {
    @Resource
    UserHolder ud;

    /**
     * 创建填充处理器, 用于填充时间
     * @return 填充处理器
     */
    @Bean
    public MetaObjectHandler metaObjectHandler() {
        return new MetaObjectHandler() {
            @Override
            public void insertFill(MetaObject metaObject) {
                this.strictInsertFill(metaObject, "createTime", LocalDateTime.class, LocalDateTime.now());
                try {
                    this.strictInsertFill(metaObject, "createBy", String.class,ud.getCurrentUser().getUsername());
                } catch (Exception e) {
                    System.err.println("获取当前用户失败");
                }
            }

            @Override
            public void updateFill(MetaObject metaObject) {
                this.strictUpdateFill(metaObject, "updateTime", LocalDateTime.class, LocalDateTime.now());
                try {
                    this.strictUpdateFill(metaObject, "updateBy", String.class,ud.getCurrentUser().getUsername());
                } catch (Exception e) {
                    System.err.println("获取当前用户失败");
                }
            }
        };
    }
}
