package com.zeroone.star.sample.service.impl;

import com.zeroone.star.sample.entity.Sample;
import com.zeroone.star.sample.mapper.SampleMapper;
import com.zeroone.star.sample.service.ISampleService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 演示示例表 服务实现类
 * </p>
 *
 * @author silvan
 * @since 2026-03-12
 */
@Service
public class SampleServiceImpl extends ServiceImpl<SampleMapper, Sample> implements ISampleService {

}
