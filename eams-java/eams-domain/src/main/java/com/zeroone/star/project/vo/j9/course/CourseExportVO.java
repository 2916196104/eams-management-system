package com.zeroone.star.project.vo.j9.course;

import com.alibaba.excel.annotation.ExcelProperty;
import com.alibaba.excel.annotation.write.style.ColumnWidth;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.math.BigDecimal;

/**
 * 课程导出 VO（EasyExcel 列映射）
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("课程导出数据")
public class CourseExportVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "课程ID", example = "1")
    @ExcelProperty("课程ID")
    @ColumnWidth(20)
    private Long id;

    @ApiModelProperty(value = "课程名称", example = "Java入门")
    @ExcelProperty("课程名称")
    @ColumnWidth(30)
    private String name;

    @ApiModelProperty(value = "学科名称", example = "计算机")
    @ExcelProperty("学科名称")
    @ColumnWidth(20)
    private String subjectName;

    @ApiModelProperty(value = "启用状态文本", example = "启用")
    @ExcelProperty("启用状态")
    @ColumnWidth(12)
    private String stateText;

    @ApiModelProperty(value = "课程总价", example = "3000.00")
    @ExcelProperty("课程总价")
    @ColumnWidth(15)
    private BigDecimal price;

    @ApiModelProperty(value = "课时单价", example = "100.00")
    @ExcelProperty("课时单价")
    @ColumnWidth(15)
    private BigDecimal unitPrice;

    @ApiModelProperty(value = "优惠金额", example = "200.00")
    @ExcelProperty("优惠金额")
    @ColumnWidth(15)
    private BigDecimal discount;

    @ApiModelProperty(value = "课次数", example = "30")
    @ExcelProperty("课次数")
    @ColumnWidth(10)
    private Integer lessonCount;

    @ApiModelProperty(value = "课堂类型文本", example = "小班课")
    @ExcelProperty("课堂类型")
    @ColumnWidth(12)
    private String lessonTypeText;

    @ApiModelProperty(value = "是否上架文本", example = "是")
    @ExcelProperty("是否上架")
    @ColumnWidth(12)
    private String forSaleText;

    @ApiModelProperty(value = "是否可预约文本", example = "是")
    @ExcelProperty("是否可预约")
    @ColumnWidth(12)
    private String bookableText;

    @ApiModelProperty(value = "库存名额", example = "50")
    @ExcelProperty("库存名额")
    @ColumnWidth(10)
    private Integer storage;
}
