package com.zeroone.star.stumanager.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.AdjustPointsDTO;
import com.zeroone.star.project.query.j8.stumanager.common.PointsRecordQuery;
import com.zeroone.star.project.vo.j8.stumanager.common.PointsRecordVO;
import com.zeroone.star.stumanager.entity.StudentCreditLog;

public interface IStudentCreditLogService extends IService<StudentCreditLog> {
    PageDTO<PointsRecordVO> queryPointsRecords(PointsRecordQuery query);

    boolean adjustPoints(AdjustPointsDTO dto);
}