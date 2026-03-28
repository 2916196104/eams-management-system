package com.zeroone.star.finance.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVO;

import java.util.List;

/**
 * 款项管理服务接口
 */
public interface FundManageService {

    /**
     * 分页查询款项列表
     * @param condition 查询条件
     * @return 分页结果
     */
    JsonVO<PageDTO<FinanceRecordDTO>> queryPage(FinanceRecordQuery condition);

    /**
     * 批量确认款项
     * @param ids 款项ID列表
     * @return 确认的ID列表
     */
    JsonVO<List<Long>> confirm(List<Long> ids);

    /**
     * 批量拒绝款项
     * @param ids 款项ID列表
     * @return 拒绝的ID列表
     */
    JsonVO<List<Long>> refuse(List<Long> ids);

    /**
     * 查询所有款项（用于导出）
     * @return 款项列表
     */
    List<FinanceRecordVO> getFinanceRecords();
}
