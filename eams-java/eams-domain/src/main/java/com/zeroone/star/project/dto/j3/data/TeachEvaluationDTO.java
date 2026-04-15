package com.zeroone.star.project.dto.j3.data;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 学评教传输对象
 */

@Data
public class TeachEvaluationDTO {
    // 教师id
    @ApiModelProperty(value="教师ID，显示教师姓名",example = "1",required = true)
    private Long teacherId;
    // 评价次数
    @ApiModelProperty(value="评价次数",example = "222")
    private Long evaluationCount;
    // 综合评分
    @ApiModelProperty(value="综合评分",example = "100")
    private Double comprehensiveScore;
    // 课室环境
    @ApiModelProperty(value="课室环境",example = "100")
    private Double classroomAtmosphere;
    // 教学态度
    @ApiModelProperty(value="教学态度",example = "100")
    private Double teachingAttitude;
    // 教学效果
    @ApiModelProperty(value="教学效果",example = "100")
    private Double teachingEffect;
}
