package com.zeroone.star.operation.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallAddDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDetailDTO;
import com.zeroone.star.project.query.j7.operation.CreditMallListQuery;
import com.zeroone.star.project.vo.JsonVO;
import java.util.List;

/**
 * 积分礼品管理服务接口
 */
public interface ICreditMallService {
    /**
     * 保存礼品
     * @param addDto
     * @return
     */
    String saveCreditMall(CreditMallAddDTO addDto);

    /**
     * 获取礼品列表
     * @param condition
     * @return
     */
    PageDTO<CreditMallDTO> listAllCreditMalls(CreditMallListQuery condition);

    /**
     * 获取指定id的礼品详情
     * @param id
     * @return
     */
    CreditMallDetailDTO getCreditMallById(String id);

    /**
     * 删除礼品（支持批量删除）
     * @param ids 礼品ID列表
     * @return 操作结果
     */
    JsonVO<String> removePointsGift(List<Long> ids);

    /**
     * 禁用/启用礼品
     * @param ids 礼品ID列表
     * @param state 状态值（0:禁用, 1:启用）
     * @return 操作结果
     */
    JsonVO<String> enablePointsGift(List<Long> ids, Integer state);
}
