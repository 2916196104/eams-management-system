package com.zeroone.star.operation.service;

import com.zeroone.star.project.dto.PageDTO;

import com.zeroone.star.project.dto.j7.operation.PointsRecordUpdateDTO;
import com.zeroone.star.project.dto.j7.operation.PointsRecordDTO;
import com.zeroone.star.project.query.j7.operation.PointsRecordQuery;
import com.zeroone.star.project.vo.JsonVO;

public interface IPointsRecordService {
    /**
     * 获取积分记录列表
     */
    JsonVO<PageDTO<PointsRecordDTO>> queryAllPointsRecord(PointsRecordQuery condition);

    /**
     * 调整积分
     */
    JsonVO<String> updatePointsRecord(java.util.List<PointsRecordUpdateDTO> updateDtos);
}
