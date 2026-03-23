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
@ApiModel("成绩导入对象")
public class GradeRecordAddDTO {

    /**
     * 学生id
     */
    @ApiModelProperty(value = "学生id", required = true)
    private Long student_id;

    /**
     * 分数
     */
    @ApiModelProperty("分数")
    private Integer score;
}

