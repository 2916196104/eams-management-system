package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;


import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：成绩单传输对象
 * </p>
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel("成绩单传输对象")
public class GradeFormDTO implements Serializable {

    @ApiModelProperty(value = "成绩单id,如果是修改数据必须传,新增不需要传", example = "2030583010845589505")
    private Long id;

    @ApiModelProperty(value = "考核项",example = "数据结构")
    private String title;

    @ApiModelProperty(value = "考核说明",example = "有选择题、填空题和编程题")
    private String info;

}
