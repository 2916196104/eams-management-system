package com.zeroone.star.sys.service.impl.template;

import com.zeroone.star.project.dto.j2.sys.Template.TemplateAttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateDTO;
import com.zeroone.star.sys.entity.Attachment;
import com.zeroone.star.sys.entity.template.SettingNotice;
import org.mapstruct.Mapper;

/**
 * <p>
 * 描述：Template模块领域模型转换器
 * </p>
 */
@Mapper(componentModel = "spring")
public interface MsTemplateMapper {
    /**
     * attachment 转换 TemplateAttachmentDTO
     * @param attachment 源对象
     * @return 目标对象
     */
    TemplateAttachmentDTO toDTO(Attachment attachment);

    SettingNotice toSettingNotice(TemplateDTO dto);
}
