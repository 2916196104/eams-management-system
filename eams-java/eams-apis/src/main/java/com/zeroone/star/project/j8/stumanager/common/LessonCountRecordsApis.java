package com.zeroone.star.project.j8.stumanager.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.LessonCountRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.common.LessonCountRecordVO;

/**
 * 消课记录
 */
public interface LessonCountRecordsApis {
    /**
     * 获取消课记录
     * @param query 查询条件
     * @return 消课记录分页列表
     */
    JsonVO<PageDTO<LessonCountRecordVO>> queryLessonCountRecords(LessonCountRecordQuery query);
}
