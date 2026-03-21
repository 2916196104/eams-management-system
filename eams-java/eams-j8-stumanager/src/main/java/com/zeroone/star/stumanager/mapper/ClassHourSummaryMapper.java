package com.zeroone.star.stumanager.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j8.stumanager.ClassHourSummaryQuery;
import com.zeroone.star.project.vo.j8.stumanager.ClassHourSummaryVO;
import org.apache.ibatis.annotations.Param;

public interface ClassHourSummaryMapper {
    Page<ClassHourSummaryVO> pageList(
            Page<ClassHourSummaryVO> page,
            @Param("query") ClassHourSummaryQuery query
    );
}
