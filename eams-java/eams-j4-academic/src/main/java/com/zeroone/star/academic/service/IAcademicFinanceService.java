package com.zeroone.star.academic.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.query.j4.student.FinanceQuery;

public interface IAcademicFinanceService {
    PageDTO<FinanceDTO> queryFinancePage(FinanceQuery query);

    FinanceDTO payDebt(FinanceDTO financeDTO);

    FinanceDTO applyRefund(FinanceDTO financeDTO);

    FinanceDTO auditRefund(FinanceDTO financeDTO);

    FinanceDTO completeRefund(FinanceDTO financeDTO);
}
