package com.zeroone.star.project.j7.operation;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallAddDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDetailDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallStateUpdateDTO;
import com.zeroone.star.project.query.j7.operation.CreditMallListQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.web.bind.annotation.RequestParam;

import javax.validation.constraints.NotBlank;
import java.util.List;

/**
 * 运营模块API接口定义
 */
public interface CreditMallApis {
    /**
     * 保存礼品
     * @param addDto
     * @return
     */
    JsonVO<String> addPointsGift(CreditMallAddDTO addDto);

    /**
     * 获取礼品列表（条件分页）
     * @param condition
     * @return
     */
    JsonVO<PageDTO<CreditMallDTO>> queryAllPointsGift(CreditMallListQuery condition);

    /**
     * 获取礼品详情
     * @param id
     * @return
     */
    JsonVO<CreditMallDetailDTO> queryById(String id);

    /**
     * 删除礼品（支持批量删除）
     * @param ids 礼品ID列表
     * @return 操作结果
     */
    JsonVO<String> removePointsGift(List<Long> ids);

    /**
     * 禁用/启用礼品
     * @param updateDTO 状态更新DTO
     * @return 操作结果
     */
    JsonVO<String> enablePointsGift(CreditMallStateUpdateDTO updateDTO);

}
