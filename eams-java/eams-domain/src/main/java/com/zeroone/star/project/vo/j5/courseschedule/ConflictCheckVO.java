package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.List;

/**
 * 冲突检查响应VO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@ApiModel(description = "冲突检查响应VO")
@Data
public class ConflictCheckVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "是否存在冲突", example = "true")
    private Boolean hasConflict;

    @ApiModelProperty(value = "冲突总数", example = "2")
    private Integer conflictCount;

    @ApiModelProperty(value = "冲突详情列表")
    private List<ConflictDetailVO> conflicts;
}
