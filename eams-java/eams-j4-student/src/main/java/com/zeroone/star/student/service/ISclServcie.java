package com.zeroone.star.student.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.CreditLogDTO;
import com.zeroone.star.project.query.j4.student.ChangeCreditQuery;
import com.zeroone.star.project.query.j4.student.CreditSelectQuery;

public interface ISclServcie {
    PageDTO<CreditLogDTO> PageCreditLog(CreditSelectQuery creditSelectQuery);

    boolean saveCreditLog(ChangeCreditQuery changeCreditQuery);
}
