package com.zeroone.star.project.dto.j6.interact;

import com.alibaba.excel.annotation.ExcelIgnore;
import com.alibaba.excel.annotation.ExcelProperty;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述:  成绩导入数据传输对象  多个成绩导入
 * </p>
 */
@Data
@ApiModel("成绩数据对象")
public class GradeRecordDTO {

    /**
     * 主键id
     */
    @ExcelIgnore //
    @ApiModelProperty(value = "唯一ID，新增不传，修改传",example = "2030583010845589505")
    private Long id;

    /**
     * 学生姓名
     */
    @ExcelProperty("*学员姓名")
    @ApiModelProperty(value = "学生姓名", hidden = true)
    private String studentName;

    /**
     * 学生id
     */
    @ExcelProperty("学生编号(选填)")
    @ApiModelProperty(value = "学生id", required = true)
    private Long studentId;

    /**
     * 成绩
     */
    @ExcelProperty("*分数")
    @ApiModelProperty(value = "成绩", example = "90")
    private Integer score;

    /**
     * 考核项id
     */
    @ExcelIgnore //
    @ApiModelProperty(value = "考核项id", required = true)
    private Long gradeId;

}