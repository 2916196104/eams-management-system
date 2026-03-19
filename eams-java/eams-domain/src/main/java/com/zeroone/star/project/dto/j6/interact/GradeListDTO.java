package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 描述：成绩列表
 */
@Data
public class GradeListDTO {

    /**
     * 成绩id
     */
    @ApiModelProperty(value = "成绩单id,如果是修改数据必须传,新增不需要传",example = "2030583010845589505")
    private Long id;

    /**
     * 序号
     */
    @ApiModelProperty(value = "序号",example = "1")
    private Long sort_id;

    /**
     * 考核项
     */
    @ApiModelProperty(value = "考核项",example = "语文")
    private String title;

    /**
     * 学生姓名
     */
    @ApiModelProperty(value = "学生姓名",example = "张三")
    private String student_name;

    /**
     * 成绩
     */
    @ApiModelProperty(value = "成绩",example = "90")
    private Double score;
}
