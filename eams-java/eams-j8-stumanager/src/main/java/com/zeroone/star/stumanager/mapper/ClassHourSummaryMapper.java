package com.zeroone.star.stumanager.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j8.stumanager.ClassHourSummaryQuery;
import com.zeroone.star.project.vo.j8.stumanager.ClassHourSummaryVO;
import com.zeroone.star.stumanager.entity.Class;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface ClassHourSummaryMapper {
    Page<ClassHourSummaryVO> pageList(
            Page<ClassHourSummaryVO> page,
            @Param("query") ClassHourSummaryQuery query
    );
}
