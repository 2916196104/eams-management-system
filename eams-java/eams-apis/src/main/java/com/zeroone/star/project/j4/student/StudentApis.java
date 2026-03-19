package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * <p>
 * 描述：学员模块财务接口
 * </p>
 */
public interface StudentApis {
    /**
     * 分页查询缴欠费与退费记录。
     *
     * @param query 查询条件
     * @return 分页结果
     */
    JsonVO<PageDTO<FinanceDTO>> queryFinancePage(FinanceQuery query);

    /**
     * 办理缴欠费。
     *
     * @param financeDTO 缴费参数
     * @return 缴费结果
     */
    JsonVO<FinanceDTO> payDebt(FinanceDTO financeDTO);

    /**
     * 发起退费申请。
     *
     * @param financeDTO 退费参数
     * @return 退费申请结果
     */
    JsonVO<FinanceDTO> applyRefund(FinanceDTO financeDTO);

    /**
     * 审核退费申请。
     *
     * @param financeDTO 审核参数
     * @return 审核结果
     */
    JsonVO<FinanceDTO> auditRefund(FinanceDTO financeDTO);

    /**
     * 完成退费。
     *
     * @param financeDTO 办结参数
     * @return 办结结果
     */
    JsonVO<FinanceDTO> completeRefund(FinanceDTO financeDTO);
}
