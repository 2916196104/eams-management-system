package com.zeroone.star.project.vo.j4.student;

import com.alibaba.excel.annotation.ExcelProperty;
import lombok.Data;
import java.io.Serializable;

/**
 * <p>
 * 描述：学员导出专用 VO
 * </p>
 */
@Data
public class StudentExportExcelVO implements Serializable {

    @ExcelProperty("ID")
    private Long id;

    @ExcelProperty("姓名")
    private String name;

    @ExcelProperty("手机号码")
    private String phone;

    @ExcelProperty("性别")
    private String gender;

    @ExcelProperty("家长姓名")
    private String parentName;

    @ExcelProperty("家长关系")
    private String familyRel;

    @ExcelProperty("学校")
    private String schoolName;

    @ExcelProperty("年级")
    private String gradeName;

    @ExcelProperty("顾问")
    private String counselorName;

    @ExcelProperty("生日")
    private String birthday;
}