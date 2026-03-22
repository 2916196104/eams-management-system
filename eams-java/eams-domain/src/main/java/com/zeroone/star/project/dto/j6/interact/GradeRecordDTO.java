package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述:  成绩导入数据传输对象  多个成绩导入
 * </p>
 *
 * @author upup
 * @version 1.0.0
 * @since 2026-03-18
 */

@Data
@ApiModel("成绩数据对象")
public class GradeRecordDTO {

    /**
     * 主键id
     */
    @ApiModelProperty(value = "唯一ID，新增不传，修改传",example = "2030583010845589505")
    private Long id;
    /**
     * 学生id
     */
    @ApiModelProperty(value = "学生id", required = true)
    private Long studentId;

    /**
     * 成绩
     */
    @ApiModelProperty(value = "成绩", example = "90")
    private Integer score;
}

