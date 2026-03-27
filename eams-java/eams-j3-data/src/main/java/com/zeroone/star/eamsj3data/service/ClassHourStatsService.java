package com.zeroone.star.eamsj3data.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j3.data.ClassHourStatsQuery;
import com.zeroone.star.project.vo.j3.data.ClassHourStatsVO;

public interface ClassHourStatsService {
    Page<ClassHourStatsVO> queryClassHourStats(ClassHourStatsQuery query);
}
