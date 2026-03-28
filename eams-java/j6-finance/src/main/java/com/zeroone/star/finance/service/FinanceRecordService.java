package com.zeroone.star.finance.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import org.springframework.stereotype.Service;

import java.util.List;

public interface FinanceRecordService {
    JsonVO<PageDTO<FinanceRecordDTO>> queryPage(FinanceRecordQuery condition);

    JsonVO<List<Long>> confirm(List<Long> ids);

    JsonVO<List<Long>> refuse(List<Long> ids);
}
