package com.zeroone.star.project.vo.j1.org;

import com.alibaba.excel.annotation.ExcelProperty;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 员工导出VO（完全匹配员工列表Excel）
 */
@Data
public class StaffExportVO {

    @ExcelProperty(value = "ID", index = 0)
    @ApiModelProperty("员工ID")
    private Long id;

    @ExcelProperty(value = "姓名", index = 1)
    @ApiModelProperty("员工姓名")
    private String name;

    @ExcelProperty(value = "手机号码", index = 2)
    @ApiModelProperty("手机号/登录账户")
    private String mobile;

    @ExcelProperty(value = "所属机构", index = 3)
    @ApiModelProperty("所属机构名称")
    private String orgName;

    @ExcelProperty(value = "职位", index = 4)
    @ApiModelProperty("职位名称")
    private String positionName;

    @ExcelProperty(value = "性别", index = 5)
    @ApiModelProperty("性别（男/女）")
    private String gender;
}