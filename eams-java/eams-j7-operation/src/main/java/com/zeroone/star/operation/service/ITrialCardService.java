package com.zeroone.star.operation.service;

import com.zeroone.star.project.dto.j7.operation.TrialPageDTO;
import com.zeroone.star.project.query.j7.operation.TrialCardQuery;
import com.zeroone.star.project.query.j7.operation.TrialRecordQuery;
import com.zeroone.star.project.vo.j7.operation.TrialCardDetailVO;
import com.zeroone.star.project.vo.j7.operation.TrialCardVO;
import com.zeroone.star.project.vo.j7.operation.TrialRecordVO;

import java.util.List;

public interface ITrialCardService {
    TrialPageDTO<TrialCardVO> queryTrialCardList(TrialCardQuery query);

    TrialCardDetailVO queryTrialCardDetail(Long id);

    TrialPageDTO<TrialRecordVO> queryTrialCardRecords(TrialRecordQuery query);

    Boolean removeTrialCard(List<Long> ids);
}
