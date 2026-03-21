package com.zeroone.star.stumanager.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.ClassHourSummaryQuery;
import com.zeroone.star.project.vo.j8.stumanager.ClassHourSummaryVO;

public interface IClassHourSummaryService{
    PageDTO<ClassHourSummaryVO> pageList(ClassHourSummaryQuery query);
}
