package com.zeroone.star.project.vo.j3.course;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.math.BigDecimal;

/**
 * <p>
 * 描述：分页展示课程信息DTO
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel("分页展示课程信息DTO")
public class CourseListVO {
    @ApiModelProperty(value = "课程ID", example = "2")
    Long id;
    @ApiModelProperty(value = "课程名称", example = "测试课程2")
    String name;
    @ApiModelProperty(value = "科目Id", example = "17")
    Long subjectId;
    @ApiModelProperty(value = "科目", example = "书法")
    String subjectName;
    @ApiModelProperty(value = "课型", example = "一对一")
    String lessonType;
    @ApiModelProperty(value = "单次价", example = "7.00")
    String unitPrice;
    @ApiModelProperty(value = "总售价", example = "100.00")
    String price;
    @ApiModelProperty(value = "课次数", example = "15")
    Integer lessonCount;
    @ApiModelProperty(value = "单位", example = "期")
    String unitName;
    @ApiModelProperty(value = "关联数", example = "1")
    Integer linkCount;
    @ApiModelProperty(value = "可预约", example = "开")
    String bookable;
    @ApiModelProperty(value = "上架状态", example = "上架中")
    String forSale;
    @ApiModelProperty(value = "库存", example = "100")
    Integer storage;
    @ApiModelProperty(value = "销售量", example = "0")
    Integer saleCount;
    @ApiModelProperty(value = "销售额", example = "0.00")
    BigDecimal saleAmount;
    @ApiModelProperty(value = "销售截至", example = "2026-05-01")
    String closeDate;
    @ApiModelProperty(value = "课程状态", example = "启用")
    String state;

}
