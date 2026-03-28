package com.zeroone.star.finance.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.MonthlyClassFeeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.MonthlyClassFeeVO;

public interface MonthlyClassFeeService {
    JsonVO<PageDTO<MonthlyClassFeeVO>> listMonthlyClassFees(MonthlyClassFeeQuery query);
}
