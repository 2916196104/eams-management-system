package com.zeroone.star.sample.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

/**
 * @description: 初始化自定义组件
 * @author: silvan
*/

@Configuration
@ComponentScan({
        "com.zeroone.star.project.components.fastdfs"
})
public class UseCusComponents {
}
