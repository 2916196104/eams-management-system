package com.zeroone.star.project.dto.j4.student;

import com.alibaba.excel.annotation.ExcelProperty;
import com.alibaba.excel.annotation.write.style.ColumnWidth;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDate;

/**
 * 结业学员导出请求DTO
 */
@Data
@ApiModel(description = "结业学员导出请求DTO")
public class StudentExportExcelDTO {
    @ExcelProperty(value = "学员ID", index = 0)
    private Long id;

    @ColumnWidth(20)
    @ExcelProperty(value = "学员姓名", index = 1)
    private String name;

    @ExcelProperty(value = "学校ID", index = 2)
    private Long schoolId;

    @ExcelProperty(value = "家长ID", index = 3)
    private Long userId;

    @ColumnWidth(30)
    @ExcelProperty(value = "结业日期", index = 4)
    private String graduationDate;

    @ExcelProperty(value = "性别", index = 5)
    private String gender;

    @ColumnWidth(40)
    @ExcelProperty(value = "备注", index = 6)
    private String remark;
}