package com.zeroone.star.finance.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dataobject.j6.finance.CashoutDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.BatchVerifyDTO;
import com.zeroone.star.project.dto.j6.finance.CashoutAddDTO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;

/**
 * 请款服务接口
 */
public interface ICashoutService extends IService<CashoutDO> {

    /**
     * 请款列表查询（条件+分页）
     * @param query 查询条件
     * @return 分页结果
     */
    PageDTO<CashoutListVO> queryCashoutPage(CashoutListQuery query);

    /**
     * 请款信息详情查询
     * @param id 请款ID
     * @return 详情VO
     */
    CashoutDetailVO getCashoutDetail(Long id);

    /**
     * 保存请款申请
     * @param cashoutAddDTO 请款数据
     * @return 新增记录ID
     */
    Long saveCashout(CashoutAddDTO cashoutAddDTO);

    /**
     * 作废请款申请
     * @param id 请款ID
     */
    void cancelCashout(Long id);

    /**
     * 批量审核请款（通过/驳回）
     * @param dto 批量审核参数
     */
    void batchVerify(BatchVerifyDTO dto);
}
