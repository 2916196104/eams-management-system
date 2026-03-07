package com.zeroone.star.sample.service.impl;

import com.alibaba.excel.util.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.sample.SampleDTO;
import com.zeroone.star.project.query.sample.SampleQuery;
import com.zeroone.star.sample.entity.Sample;
import com.zeroone.star.sample.mapper.SampleMapper;
import com.zeroone.star.sample.service.ISampleService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * <p>
 * 演示示例表 服务实现类
 * </p>
 * @author 阿伟
 * @since 2026-03-07
 */
@Service
public class SampleServiceImpl extends ServiceImpl<SampleMapper, Sample> implements ISampleService {

    @Resource
    MsSampleMapper msSampleMapper;

    @Override
    public PageDTO<SampleDTO> listAll(SampleQuery query) {
        // 构建分页查询对象
        Page<Sample> page = new Page<>(query.getPageIndex(), query.getPageSize());
        // 构建查询条件
        QueryWrapper<Sample> queryWrapper = new QueryWrapper<>();
        queryWrapper.like(!StringUtils.isEmpty(query.getName()), "name", query.getName());
        queryWrapper.orderBy(true, false, "IFNULL(`update_time`,`create_time`)");
        queryWrapper.orderBy(true, false, "id");
        // 分页查询
        Page<Sample> result = baseMapper.selectPage(page, queryWrapper);
        return PageDTO.create(result, src -> msSampleMapper.toDTO(src));
    }

    @Override
    public SampleDTO getById(String id) {
        Sample sample = baseMapper.selectById(id);
        if (sample != null) {
            return msSampleMapper.toDTO(sample);
        }
        return null;
    }
}
