package com.zeroone.star.project.j6.finance;

import com.zeroone.star.project.dto.PageDTO;
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
}