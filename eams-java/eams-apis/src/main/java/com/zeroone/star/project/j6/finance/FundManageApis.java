package com.zeroone.star.project.j6.finance;

import javax.servlet.http.HttpServletResponse;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.io.IOException;
import java.util.List;

/**
 * 款项管理Apis
 */
public interface FundManageApis {
    /**
     * 获取款项列表（条件+分页）
     * @param condition 查询条件
     * @return 款项信息
     */
    JsonVO<PageDTO<FinanceRecordDTO>> queryPage(FinanceRecordQuery condition);

    /**
     * 批量确认
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

    /**
     * 导出，返回下载链接
     * @param response
     * @return 下载链接
     * @throws IOException
     */
    JsonVO<String> download(HttpServletResponse response) throws IOException;
}
