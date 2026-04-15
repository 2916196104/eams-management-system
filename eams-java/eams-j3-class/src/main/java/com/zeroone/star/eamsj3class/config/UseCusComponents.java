package com.zeroone.star.eamsj3class.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

/**
 * @authore Longan
 * @description
 */
@Configuration
@ComponentScan({
        "com.zeroone.star.project.components.easyexcel",
        "com.zeroone.star.project.components.fastdfs"
})
public class UseCusComponents {
}
