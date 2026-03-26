package com.zeroone.star.finance.service;

import com.zeroone.star.finance.entity.Cashout;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dataobject.j6.finance.CashoutDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;

public interface ICashoutService extends IService<CashoutDO> {
    /**
     * 请款列表查询（条件+分页）
     */
    PageDTO<CashoutListVO> queryCashoutPage(CashoutListQuery query);

    /**
     * 请款信息详情查询
     */
    CashoutDetailVO getCashoutDetail(Long id);
}
