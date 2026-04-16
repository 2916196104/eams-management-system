package com.zeroone.star.project.dto.j7.interaction;

import com.alibaba.excel.annotation.ExcelProperty;
import lombok.Data;

@Data
public class ScoreImportExcelDTO {
    /**
     * 学员姓名（必填），对应Excel第一列
     */
    @ExcelProperty(value = "*学员姓名", index = 0)
    private String studentName;

    /**
     * 学生编号（选填），对应Excel第二列
     */
    @ExcelProperty(value = "学生编号(选填)", index = 1)
    private Long studentCode;

    /**
     * 分数（必填），对应Excel第三列
     */
    @ExcelProperty(value = "*分数", index = 2)
    private Integer score;
}