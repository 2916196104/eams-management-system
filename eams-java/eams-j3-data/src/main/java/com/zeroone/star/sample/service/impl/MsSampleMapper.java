package com.zeroone.star.sample.service.impl;

import com.zeroone.star.project.dto.sample.SampleAddDTO;
import com.zeroone.star.project.dto.sample.SampleDTO;
import com.zeroone.star.sample.entity.Sample;
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
public interface MsSampleMapper {
    /**
     * sample 转换 sampleDTO
     * @param sample 源对象
     * @return 目标对象
     */
    SampleDTO toDTO(Sample sample);

    /**
     * sampleAddDTO 转换 sample
     * @param dto 源对象
     * @return 目标对象
     */
    Sample addDtoToDo(SampleAddDTO dto);

    /**
     * sampleDTO 转换 sampleAddDTO
     * @param dto 源对象
     * @return 目标对象
     */
    Sample dtoToDo(SampleDTO dto);
}
