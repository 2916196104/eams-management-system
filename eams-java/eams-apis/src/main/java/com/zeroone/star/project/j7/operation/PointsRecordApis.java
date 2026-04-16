package com.zeroone.star.project.j7.operation;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.PointsRecordDTO;
import com.zeroone.star.project.dto.j7.operation.PointsRecordUpdateDTO;
import com.zeroone.star.project.query.j7.operation.PointsRecordQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * 运营模块API接口定义
 */

public interface PointsRecordApis {

    /**
     * 获取积分记录（条件分页）
     * @param condition
     * @return
     */
    JsonVO<PageDTO<PointsRecordDTO>> queryAllPointsRecord(PointsRecordQuery condition);

    /**
     * 调整积分
     * @param updateDto
     * @return
     */
    JsonVO<String> updatePointsRecord(PointsRecordUpdateDTO updateDto);

}