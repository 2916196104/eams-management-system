package com.zeroone.star.project.j9.operation;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.CreditExchangeBatchAuditDTO;
import com.zeroone.star.project.query.j9.operation.CreditExchangeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeBatchAuditVO;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeVO;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.RequestBody;

public interface CreditExchangeApis {
    /**
     * 条件分页查询积分兑换申请列表
     * @param condition
     * @return
     */
    JsonVO<PageDTO<CreditExchangeVO>> queryAll(CreditExchangeQuery condition);

    /**
     * 批量审核兑换申请
     * @param auditDTO
     * @return
     */
    JsonVO<CreditExchangeBatchAuditVO> modifyExchangeAudit(@Validated @RequestBody CreditExchangeBatchAuditDTO auditDTO);
}
