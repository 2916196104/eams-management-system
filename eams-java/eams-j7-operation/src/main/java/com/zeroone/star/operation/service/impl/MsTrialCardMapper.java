package com.zeroone.star.operation.service.impl;

import com.zeroone.star.project.dto.j7.operation.TrialCardDTO;
import com.zeroone.star.project.dto.j7.operation.TrialCardDetailDTO;
import com.zeroone.star.project.dto.j7.operation.TrialRecordDTO;
import com.zeroone.star.project.vo.j7.operation.TrialCardDetailVO;
import com.zeroone.star.project.vo.j7.operation.TrialCardVO;
import com.zeroone.star.project.vo.j7.operation.TrialRecordVO;
import com.zeroone.star.operation.entity.CourseTrial;
import com.zeroone.star.operation.entity.CourseTrialRecord;
import org.mapstruct.Mapper;

@Mapper(componentModel = "spring")
public interface MsTrialCardMapper {

    // 1. 列表转换：Entity -> VO
    TrialCardVO toVO(CourseTrial entity);

    // 2. 详情转换：Entity -> DetailVO
    TrialCardDetailVO toDetailVO(CourseTrial entity);

    // 3. 记录转换：Entity -> RecordVO
    TrialRecordVO toRecordVO(CourseTrialRecord entity);
    TrialCardDTO toListDTO(com.zeroone.star.operation.entity.CourseTrial entity);
    TrialCardDetailDTO toDetailDTO(com.zeroone.star.operation.entity.CourseTrial entity);
    TrialRecordDTO toRecordDTO(com.zeroone.star.operation.entity.CourseTrialRecord entity);
}