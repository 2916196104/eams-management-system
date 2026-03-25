package com.zeroone.star.eamsj3data.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.eamsj3data.mapper.ClassHourStatsMapper;
import com.zeroone.star.eamsj3data.service.ClassHourStatsService;
import com.zeroone.star.project.query.j3.data.ClassHourStatsQuery;
import com.zeroone.star.project.vo.j3.data.ClassHourStatsVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;


@Service
public class ClassHourStatsServiceImpl implements ClassHourStatsService {

    @Autowired
    private ClassHourStatsMapper classHourStatsMapper;
    @Override
    public Page<ClassHourStatsVO> queryClassHourStats(ClassHourStatsQuery query) {
        Page<ClassHourStatsVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        Long total = classHourStatsMapper.selectClassHourStatsCount(query.getStartDate(), query.getEndDate());
        page.setTotal(total);
        classHourStatsMapper.selectClassHourStats(page, query.getStartDate(), query.getEndDate());
        return page;
    }
}
