package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 成绩列表数据对象
 */
@Data
@ApiModel("成绩列表数据对象")
public class GradeListDTO {

    /**
     * 成绩id
     */
    @ApiModelProperty(value = "成绩单id,如果是修改数据必须传,新增不需要传",example = "2030583010845589505")
    private Long id;

    /**
     * 成绩单id
     */
    @ApiModelProperty(value = "成绩单id", example = "1")
    private Long gradeId;

    /**
     * 考核项
     */
    @ApiModelProperty(value = "考核项",example = "语文")
    private String title;

    @ApiModelProperty(value = "学生ID", example = "20230001", required = true)
    private Long studentId;
    /**
     * 学生姓名
     */
    @ApiModelProperty(value = "学生姓名", example = "阿良")
    private String studentName;

    /**
     * 成绩
     */
    @ApiModelProperty(value = "成绩",example = "90")
    private Double score;
}
