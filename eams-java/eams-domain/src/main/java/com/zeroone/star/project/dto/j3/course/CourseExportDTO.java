package com.zeroone.star.project.dto.j3.course;

import com.alibaba.excel.annotation.ExcelProperty;
import lombok.Data;
import java.math.BigDecimal;

@Data
public class CourseExportDTO {
    @ExcelProperty("课程")
    private String SubjectId;

    @ExcelProperty("课程名")
    private String name;

    @ExcelProperty("价格")
    private BigDecimal price;

    @ExcelProperty("单价")
    private BigDecimal unitPrice;

    @ExcelProperty("课次数")
    private BigDecimal lessonCount;

    @ExcelProperty("课堂类型")
    private Integer lessonType;
}