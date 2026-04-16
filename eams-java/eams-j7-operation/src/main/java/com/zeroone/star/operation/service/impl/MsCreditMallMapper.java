package com.zeroone.star.operation.service.impl;

import com.zeroone.star.operation.entity.CreditMall;
import com.zeroone.star.project.dto.j7.operation.CreditMallAddDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDetailDTO;
import org.mapstruct.Mapper;

/**
 * <p>
 * 描述：Sample模块领域模型转换器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Mapper(componentModel = "spring")
public interface MsCreditMallMapper {
    /**
     * CreditMall 转换 CreditMallDTO
     * @param creditMall 源对象
     * @return 目标对象
     */
    CreditMallDTO toDTO(CreditMall creditMall);

    /**
     * CreditMallAddDTO 转换 CreditMall
     * @param dto 源对象
     * @return 目标对象
     */
    CreditMall addDtoToDo(CreditMallAddDTO dto);

    /**
     * CreditMall 转换 CreditMallDetailDTO
     * @param creditMall 源对象
     * @return 目标对象
     */
    CreditMallDetailDTO DetailDtoToDTo(CreditMall creditMall);

}
