package com.zeroone.star.eamsj3supplies.mapstruct;

import com.zeroone.star.project.DO.MaterialRecord;
import com.zeroone.star.project.dto.j3.supplies.MaterialStockChangedDTO;
import com.zeroone.star.project.vo.j3.supplies.MaterialRecordVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialStockVO;
import org.mapstruct.Mapper;

import java.util.List;

@Mapper(componentModel = "spring")
public interface MaterialStructMapper {
    MaterialStockVO toMaterialStockVO(MaterialStockChangedDTO changedDTO);

    MaterialRecordVO toMaterialRecordVO(MaterialRecord recordDO);

    List<MaterialRecordVO> toMaterialRecordVOList(List<MaterialRecord> recordDOList);
}
