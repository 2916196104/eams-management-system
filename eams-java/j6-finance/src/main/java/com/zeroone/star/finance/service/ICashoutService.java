package com.zeroone.star.finance.service;

import com.zeroone.star.finance.entity.Cashout;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j6.finance.BatchVerifyDTO;

public interface ICashoutService extends IService<Cashout> {

    /**
     * 批量审核请款（通过/驳回）
     * @param dto 批量审核参数
     */
    void batchVerify(BatchVerifyDTO dto);
}
