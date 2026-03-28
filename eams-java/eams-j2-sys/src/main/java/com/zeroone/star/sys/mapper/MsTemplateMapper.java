package com.zeroone.star.sys.mapper;

import com.zeroone.star.project.dto.j2.sys.Template.TemplateDTO;
import com.zeroone.star.sys.entity.Attachment;
import org.mapstruct.Mapper;

/**
 * <p>
 * 描述：Template模块领域模型转换器
 * </p>
 */
@Mapper(componentModel = "spring")
public interface MsTemplateMapper {
    /**
     * attachment 转换 TemplateDTO
     * @param attachment 源对象
     * @return 目标对象
     */
    TemplateDTO toDTO(Attachment attachment);
}
