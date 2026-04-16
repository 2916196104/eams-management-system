package com.zeroone.star.stumanager.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.LessonCountRecordQuery;
import com.zeroone.star.project.vo.j8.stumanager.common.LessonCountRecordVO;
import com.zeroone.star.stumanager.entity.StudentLessonCountLog;
import com.baomidou.mybatisplus.extension.service.IService;

public interface IStudentLessonCountLogService extends IService<StudentLessonCountLog> {
    PageDTO<LessonCountRecordVO> queryLessonCountRecords(LessonCountRecordQuery query);
}