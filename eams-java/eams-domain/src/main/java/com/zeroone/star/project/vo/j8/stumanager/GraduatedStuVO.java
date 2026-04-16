package com.zeroone.star.project.vo.j8.stumanager;

import com.alibaba.excel.annotation.ExcelProperty;
import com.alibaba.excel.annotation.format.DateTimeFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
public class GraduatedStuVO {
    @ExcelProperty(value = "ID", index = 0)
    @ApiModelProperty(value = "学员ID", example = "2")
    private Long id;
    
    @ExcelProperty(value = "姓名", index = 1)
    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String name;
    
    @ExcelProperty(value = "手机号码", index = 2)
    @ApiModelProperty(value = "电话号码", example = "17145214523")
    private String phone;
    
    @ExcelProperty(value = "性别", index = 3)
    @ApiModelProperty(value = "性别", example = "男")
    private String sex;
    
    @ExcelProperty(value = "家长姓名", index = 4)
    @ApiModelProperty(value = "家长姓名", example = "张无")
    private String parentName;
    
    @ExcelProperty(value = "家长关系", index = 5)
    @ApiModelProperty(value = "家庭关系", example = "直系亲属")
    private String familyRel;
    
    @ExcelProperty(value = "学校", index = 6)
    @ApiModelProperty(value = "学校", example = "xx")
    private String school;
    
    @ExcelProperty(value = "年级", index = 7)
    @ApiModelProperty(value = "年级", example = "xx")
    private String grade;
    
    @ExcelProperty(value = "顾问", index = 8)
    @ApiModelProperty(value = "辅导员", example = "xxx")
    private String counselor;
    
    @ExcelProperty(value = "生日", index = 9)
    @ApiModelProperty(value = "生日", example = "2005-10-01", dataType = "java.lang.String")
    @DateTimeFormat("yyyy-MM-dd")
    private LocalDate birthday;
}