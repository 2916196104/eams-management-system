package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotNull;

/**
 * 作业点评数据传输对象
 */
@Data
@ApiModel("作业点评数据传输对象")
public class HomeworkScoreDto {

    /**
     * 提交记录ID
     */
    @NotNull(message = "提交记录ID不能为空")
    @ApiModelProperty(value = "提交记录ID", required = true, example = "2030583010845589505")
    private Long id;

    /**
     * 点评分数
     */
    @NotNull(message = "点评分数不能为空")
    @Min(value = 0, message = "分数不能小于0")
    @Max(value = 100, message = "分数不能大于100")
    @ApiModelProperty(value = "点评分数", required = true, example = "90")
    private Integer score;

    /**
     * 点评内容
     */
    @ApiModelProperty(value = "点评内容", example = "作业完成得很好，继续加油！")
    private String comment;
}
