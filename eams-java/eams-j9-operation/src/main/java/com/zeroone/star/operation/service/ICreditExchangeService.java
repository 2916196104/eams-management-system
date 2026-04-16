package com.zeroone.star.operation.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.operation.entity.CreditExchangeDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.CreditExchangeBatchAuditDTO;
import com.zeroone.star.project.query.j9.operation.CreditExchangeQuery;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeBatchAuditVO;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeVO;

/**
 * 积分商城兑换记录 服务接口
 */
public interface ICreditExchangeService extends IService<CreditExchangeDO> {

    /**
     * 分页查询兑换申请列表
     * @param condition 查询条件
     * @return 分页列表
     */
    PageDTO<CreditExchangeVO> listCreditExchanges(CreditExchangeQuery condition);

    /**
     * 批量审核兑换申请
     * @param auditDTO 审核数据
     * @return 审核结果
     */
    CreditExchangeBatchAuditVO updateExchangeAudit(CreditExchangeBatchAuditDTO auditDTO);
}
