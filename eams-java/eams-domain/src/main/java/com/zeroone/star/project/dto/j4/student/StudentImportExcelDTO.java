package com.zeroone.star.project.dto.j4.student;

import com.alibaba.excel.annotation.ExcelProperty;
import lombok.Data;
/**
 * 结业学员导入请求DTO
 */

@Data
public class StudentImportExcelDTO {
    @ExcelProperty(value = "学员姓名", index = 0)
    private String name;

    @ExcelProperty(value = "学校ID", index = 1)
    private String schoolId;

    @ExcelProperty(value = "家长ID", index = 2)
    private String userId;

    @ExcelProperty(value = "结业日期", index = 3)
    private String  graduationDate;

    @ExcelProperty(value = "性别 1男0女", index = 4)
    private String gender;

    @ExcelProperty(value = "备注", index = 5)
    private String remark;
}