package com.zeroone.star.project.j6.finance;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface FinanceRecordApis {
    /**
     * 分页查询款项信息
     * @param condition 查询条件
     * @return 款项信息
     */
    JsonVO<PageDTO<FinanceRecordDTO>> queryPage(FinanceRecordQuery condition);

    /**
     * 批量认款
     * @param ids 财务记录id
     * @return 修改款项信息
     */
    JsonVO<List<Long>> confirm(List<Long> ids);

    /**
     * 批量拒绝
     * @param ids 财务记录id
     * @return 修改款项信息
     */
    JsonVO<List<Long>> refuse(List<Long> ids);
}
