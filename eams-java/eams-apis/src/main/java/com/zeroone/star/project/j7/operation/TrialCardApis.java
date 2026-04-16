package com.zeroone.star.project.j7.operation;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.*;
import com.zeroone.star.project.vo.j7.operation.*;
import com.zeroone.star.project.query.j7.operation.TrialCardQuery;
import com.zeroone.star.project.query.j7.operation.TrialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface TrialCardApis {
    /**
     * 获取试听卡列表
     *
     * @param query
     * @return
     */
    JsonVO<TrialPageDTO<TrialCardVO>> queryTrialCardList(TrialCardQuery query);

    /**
     * 获取试听卡详情
     *
     * @param id
     * @return
     */
    JsonVO<TrialCardDetailVO> queryTrialCardDetail(Long id);

    /**
     * 获取试听卡领取记录
     *
     * @param query
     * @return
     */
    JsonVO<TrialPageDTO<TrialRecordVO>> queryTrialCardRecords(TrialRecordQuery query);

    /**
     * 删除试听卡
     * @param ids
     * @return
     */
    JsonVO<Boolean> removeTrialCard(List<Long> ids);

    /**
     * 新增保存演示卡
     * @param demoCardDTO 演示卡信息
     * @return 演示卡ID
     * @author 1
     * @version 1.0.0
     * @date 2026-3-16
     */
    JsonVO<Long> saveDemoCard(DemoCardDTO demoCardDTO);

}
