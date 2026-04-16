package com.zeroone.star.project.j8.stumanager.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.AdjustPointsDTO;
import com.zeroone.star.project.query.j8.stumanager.common.PointsRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.common.PointsRecordVO;

/**
 * 积分记录
 */
public interface PointsRecordsApis {
    /**
     * 获取积分记录
     * @param query 查询条件
     * @return 积分记录分页列表
     */
    JsonVO<PageDTO<PointsRecordVO>> queryPointsRecords(PointsRecordQuery query);

    /**
     * 调整积分
     * @param dto 调整积分参数
     * @return 调整结果
     */
    JsonVO<Boolean> adjustPoints(AdjustPointsDTO dto);
}
