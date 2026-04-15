package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：签到保存参数
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Data
@ApiModel(value = "签到保存参数", description = "批量设置学员上课签到状态")
public class LessonSignSaveDTO {

    @ApiModelProperty(value = "课次ID", required = true, example = "1")
    @NotNull(message = "课次ID不能为空")
    private Long lessonId;

    @ApiModelProperty(value = "学员ID", required = true, example = "1")
    @NotNull(message = "学员ID不能为空")
    private Long studentId;

    @ApiModelProperty(value = "签到状态", required = true, notes = "0-未签到,1-已签到,2-迟到签到,3-请假,4-旷课", example = "1")
    private Integer state;

    @ApiModelProperty(value = "签到方式", example = "1")
    private Integer signType;
}
