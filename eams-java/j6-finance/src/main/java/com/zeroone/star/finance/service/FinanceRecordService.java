package com.zeroone.star.finance.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVO;
import org.springframework.stereotype.Service;

import java.util.List;

public interface FinanceRecordService {
    JsonVO<PageDTO<FinanceRecordVO>> queryPage(FinanceRecordQuery condition);

    JsonVO<List<Long>> confirm(List<Long> ids);

    JsonVO<List<Long>> refuse(List<Long> ids);
}
