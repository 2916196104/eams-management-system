package com.zeroone.star.project.j1.orgmanager.mapstruct;

import com.zeroone.star.project.DO.PositionDataPermissionDO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import org.mapstruct.Mapper;

@Mapper(componentModel = "spring")
public interface DataPermissionConvert {

    /**
     * dtoToDo 把DTO转换为DO
     * @param dto 传入对象
     * @return 目标DO
     */
     PositionDataPermissionDO dtoToDo (PositionDataPermissionDTO dto);

    /**
     * doToDto 把TO转换为DTO
     * @param Do 传入对象
     * @return 目标DTO
     */
    PositionDataPermissionDTO doToDto(PositionDataPermissionDO Do);

}
