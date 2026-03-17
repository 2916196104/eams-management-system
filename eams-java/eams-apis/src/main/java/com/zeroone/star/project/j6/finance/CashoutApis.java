package com.zeroone.star.project.j6.finance;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.CashoutAddDTO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;

/**
 * 请款管理接口
 */
public interface CashoutApis {

    /**
     * 请款列表查询（条件+分页）
     *
     * @param query 查询条件 + 分页参数
     * @return 分页后的请款列表
     */
    JsonVO<PageDTO<CashoutListVO>> queryCashoutPage(CashoutListQuery query);

    /**
     * 请款信息详情查询
     *
     * @param id 请款单ID
     * @return 请款信息详情
     */
    JsonVO<CashoutDetailVO> getCashoutDetail(Long id);

    /**
     * 保存请款申请
     * @param cashoutAddDTO 请款数据
     * @return 保存结果
     */
    JsonVO<Long> saveCashout(CashoutAddDTO cashoutAddDTO);

    /**
     * 作废请款申请
     * @param id 请款ID
     * @return 作废结果
     */
    JsonVO<Long> cancelCashout(Long id);
}