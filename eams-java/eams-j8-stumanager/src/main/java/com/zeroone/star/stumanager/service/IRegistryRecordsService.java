package com.zeroone.star.stumanager.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.PayOverdueDTO;
import com.zeroone.star.project.dto.j8.stumanager.RefundDTO;
import com.zeroone.star.project.dto.j8.stumanager.RegistryRecordsDTO;
import com.zeroone.star.project.query.j8.stumanager.RegistryRecordsQuery;

public interface IRegistryRecordsService {

    /**
     * 分页查询报名记录
     * @param condition 查询条件
     * @return 报名记录分页数据
     */
    PageDTO<RegistryRecordsDTO> queryRegistryRecords(RegistryRecordsQuery condition);

    /**
     * 缴纳欠费
     * @param dto 欠费信息
     * @param id 学生课程表 id
     * @return 处理结果
     */
    String modifyPayOverdue(PayOverdueDTO dto, Long id);

    /**
     * 退费处理
     * @param dto 退费信息
     * @param id 学生课程表 id
     * @return 处理结果
     */
    String modifyRefund(RefundDTO dto, Long id);
}
