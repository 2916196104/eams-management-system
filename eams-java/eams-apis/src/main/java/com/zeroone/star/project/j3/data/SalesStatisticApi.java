package com.zeroone.star.project.j3.data;

import com.zeroone.star.project.dto.j3.data.CourseHistoryTotalDTO;
import com.zeroone.star.project.dto.j3.data.SignUpTrendDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.time.LocalDateTime;
import java.util.List;

/**
 * 销售统计接口
 */
public interface SalesStatisticApi {
    /**
     * 报名趋势(默认是本月)
     * @param startDate 开始时间
     * @param endDate 结束时间
     * @return 报名数据信息
     */
    JsonVO<List<SignUpTrendDTO>> courseSaleByDay(LocalDateTime startDate, LocalDateTime endDate);

    /**
     * 课程历史总销量（默认是全部的）
     * @param startDate 开始日期
     * @param endDate 结束日期
     * @return
     */
    JsonVO<List<CourseHistoryTotalDTO>> courseSalesTotal(LocalDateTime startDate, LocalDateTime endDate);
}
