package com.zeroone.star.project.dto.j8.stumanager.OnlineStu;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
/**
 * <p>
 * 描述：修改顾问
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 麦
 * @version 1.0.0
 */
@Data
@ApiModel(value = "学员顾问信息", description = "用于修改学员顾问的请求数据")
public class StudentAdvisorDTO {

    @ApiModelProperty(value = "学员ID", required = true, example = "1001")
    private Long studentId;

    @ApiModelProperty(value = "新顾问ID", required = true, example = "2001")
    private Long advisorId;

    @ApiModelProperty(value = "新顾问姓名", required = true, example = "张老师")
    private String advisorName;

}
