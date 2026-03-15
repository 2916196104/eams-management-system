package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface StudentApis {
    /**
     * 获取跟进记录列表（条件+分页）
     * @param condition 查询条件
     * @return 分页结果
     */
    JsonVO<PageDTO<FollowUpDTO>> queryFollowUpPage(FollowUpQuery condition);

    /**
     * 添加/修改跟进记录
     * @param followUpDTO 跟进记录信息
     * @return 保存后的ID
     */
    JsonVO<Long> saveFollowUp(FollowUpDTO followUpDTO);

    /**
     * 删除跟进记录（支持批量删除）
     * @param ids 跟进记录ID列表
     * @return 删除成功的ID列表
     */
    JsonVO<List<Long>> deleteFollowUp(List<Long> ids);

    /**
     * 获取单个跟进记录详情 (复用DTO，用于编辑前回填或查看详情)
     * @param id 跟进记录ID
     * @return 跟进记录详情
     */
    JsonVO<FollowUpDTO> getFollowUpDetail(Long id);
}