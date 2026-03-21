package com.zeroone.star.stumanager.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.ClassHourSummaryQuery;
import com.zeroone.star.project.vo.j8.stumanager.ClassHourSummaryVO;
import com.zeroone.star.stumanager.mapper.ClassHourSummaryMapper;
import com.zeroone.star.stumanager.service.IClassHourSummaryService;
import org.springframework.stereotype.Service;
import javax.annotation.Resource;

@Service
public class ClassHourSummaryServiceImpl implements IClassHourSummaryService {

    @Resource
    private ClassHourSummaryMapper classHourSummaryMapper;

    @Override
    public PageDTO<ClassHourSummaryVO> pageList(ClassHourSummaryQuery query) {
        Page<ClassHourSummaryVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        Page<ClassHourSummaryVO> result = classHourSummaryMapper.pageList(page, query);
        PageDTO<ClassHourSummaryVO> pageDTO = new PageDTO<>();
        pageDTO.setTotal(result.getTotal());
        pageDTO.setPages(result.getPages());
        return pageDTO;
    }
}