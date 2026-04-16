package com.zeroone.star.project.j8.stumanager;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.ClassHourSummaryQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.ClassHourSummaryVO;

/**
 * 课时汇总
 */
public interface ClassHourSummaryApis {

    JsonVO<PageDTO<ClassHourSummaryVO>> getLessonSummary(ClassHourSummaryQuery query);
}
