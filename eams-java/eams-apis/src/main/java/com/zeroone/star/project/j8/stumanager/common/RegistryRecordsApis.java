package com.zeroone.star.project.j8.stumanager.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.PayOverdueDTO;
import com.zeroone.star.project.dto.j8.stumanager.RefundDTO;
import com.zeroone.star.project.dto.j8.stumanager.RegistryRecordsDTO;
import com.zeroone.star.project.query.j8.stumanager.RegistryRecordsQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * 报名记录
 */
public interface RegistryRecordsApis {

    /**
     *分页查询报名记录
     * @param condition 查询条件
     * @return 报名记录
     */
    JsonVO<PageDTO<RegistryRecordsDTO>> queryRegistryRecords(RegistryRecordsQuery condition);

    /**
     *退款
     * @param dto 退款信息
     * @param id 学生课程表id
     * @return 退款结果
     */
    JsonVO<String> modifyRefund(RefundDTO dto, Long id);

    /**
     *缴纳欠费
     * @param dto 缴纳欠费信息
     * @param id 学生课程表id
     * @return 缴纳欠费结果
     */
    JsonVO<String> modifyPayOverdue(PayOverdueDTO dto, Long id);

}
