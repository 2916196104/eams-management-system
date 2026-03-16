package com.zeroone.star.sample.service;

import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.web.bind.annotation.PostMapping;

/**
 * <p>
 * 描述：TODO
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@FeignClient(name = "${sn.seata}")
public interface ISeataFeignService {
    @PostMapping("/seata/testSave")
    Integer testSave();
}
