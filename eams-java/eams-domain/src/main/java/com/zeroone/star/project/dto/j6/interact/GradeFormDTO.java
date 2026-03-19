package com.zeroone.star.project.dto.j6.interact;

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
public class GradeFormDTO implements Serializable {

    @ApiModelProperty(value = "考核项",example = "数据结构")
    private String title;

    @ApiModelProperty(value = "考核说明",example = "有选择题、填空题和编程题")
    private String info;

    @ApiModelProperty(value = "发布者",example = "管理员")
    private String creator;

    @ApiModelProperty(value = "发布时间",example = "2026-03-10 21:17")
    private LocalDateTime addTime;
}
