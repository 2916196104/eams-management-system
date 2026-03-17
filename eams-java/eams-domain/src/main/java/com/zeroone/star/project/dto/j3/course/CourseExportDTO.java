package com.zeroone.star.project.dto.j3.course;

import com.alibaba.excel.annotation.ExcelProperty;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import java.math.BigDecimal;

@Getter
@Setter
public class CourseExportDTO {
    @ExcelProperty(value = "课程", index = 0)
    private String SubjectId;

    @ExcelProperty(value = "课程名", index = 1)
    private String name;

    @ExcelProperty(value = "价格", index = 2)
    private BigDecimal price;

    @ExcelProperty(value = "单价", index = 3)
    private BigDecimal unitPrice;

    @ExcelProperty(value = "课次数", index = 4)
    private BigDecimal lessonCount;

    @ExcelProperty(value = "课堂类型", index = 5)
    private Integer lessonType;
}