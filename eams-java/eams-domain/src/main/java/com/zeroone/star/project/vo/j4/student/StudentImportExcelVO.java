package com.zeroone.star.project.vo.j4.student;

import com.alibaba.excel.annotation.ExcelProperty;
import lombok.Data;
import java.io.Serializable;

/**
 * <p>
 * 描述：学员导入专用 VO (严格对应你的截图)
 * </p>
 */
@Data
public class StudentImportExcelVO implements Serializable {

    @ExcelProperty(index = 0)
    private String studentName; // *姓名

    @ExcelProperty(index = 1)
    private String phone;       // *手机号

    @ExcelProperty(index = 2)
    private String password;    // *登录密码

    @ExcelProperty(index = 3)
    private String parentName;  // 家长姓名

    @ExcelProperty(index = 4)
    private String gender;      // 有效值:男|女

    @ExcelProperty(index = 5)
    private String birthday;    // 格式:2000-01-01

    @ExcelProperty(index = 6)
    private String idcard;      // 身份证


    @ExcelProperty(index = 7, value = "错误原因")
    private String errorMessage; 
}