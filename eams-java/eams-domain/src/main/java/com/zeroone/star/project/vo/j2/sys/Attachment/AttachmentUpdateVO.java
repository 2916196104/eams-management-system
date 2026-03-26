// src/main/java/com/zeroone/star/project/vo/j2/sys/AttachmentUpdateVO.java
package com.zeroone.star.project.vo.j2.sys.Attachment;

import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentDTO;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;


import java.time.LocalDateTime;

/**
 * <p>
 * 描述：附件修改结果
 * </p>
 * @author 大鹏
 * @version 1.0.0
 */
@EqualsAndHashCode(callSuper = true)
@Data
@ApiModel("附件修改结果")
public class AttachmentUpdateVO extends AttachmentDTO {

    @ApiModelProperty(value = "最后修改人姓名", example = "李四")
    private String lastModifierName;

    @ApiModelProperty(value = "修改时间（格式化）", example = "2024-03-18 15:30:00")
    private String updateTimeFormatted;

    @ApiModelProperty(value = "操作结果", example = "修改成功")
    private String operationResult;

    public static AttachmentUpdateVO fromDTO(AttachmentDTO dto, String modifierName) {
        AttachmentUpdateVO vo = new AttachmentUpdateVO();
        // 复制所有字段
        org.springframework.beans.BeanUtils.copyProperties(dto, vo);

        // 设置额外字段
        vo.setLastModifierName(modifierName);
        vo.setUpdateTimeFormatted(formatDateTime(java.time.LocalDateTime.now()));
        vo.setOperationResult("修改成功");

        return vo;
    }

    private static String formatDateTime(LocalDateTime dateTime) {
        if (dateTime == null) return "";
        java.time.format.DateTimeFormatter formatter =
                java.time.format.DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        return dateTime.format(formatter);
    }
}
