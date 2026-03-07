package com.zeroone.star.sample.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.sample.SampleDTO;
import com.zeroone.star.project.query.sample.SampleQuery;
import com.zeroone.star.sample.entity.Sample;
import com.baomidou.mybatisplus.extension.service.IService;

/**
 * <p>
 * 演示示例表 服务类
 * </p>
 * @author 阿伟
 * @since 2026-03-07
 */
public interface ISampleService extends IService<Sample> {
    /**
     * 分页条件查询数据
     * @param query 查询参数
     * @return 所有数据
     */
    PageDTO<SampleDTO> listAll(SampleQuery query);

    /**
     * 根据id查询数据
     * @param id 数据id
     * @return 数据
     */
    SampleDTO getById(String id);
}
