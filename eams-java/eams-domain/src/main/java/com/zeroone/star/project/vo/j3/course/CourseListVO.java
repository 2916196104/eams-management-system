package com.zeroone.star.project.vo.j3.course;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;

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
@ApiModel("分页展示课程信息DTO")
public class CourseListVO {
    @ApiModelProperty(name = "课程ID", example = "2")
    Long id;
    @ApiModelProperty(name = "课程名称", example = "测试课程2")
    String name;
    @ApiModelProperty(name = "科目Id", example = "17")
    Long subjectId;
    @ApiModelProperty(name = "科目", example = "书法")
    String subjectName;
    @ApiModelProperty(name = "课型", example = "一对一")
    String lessonType;
    @ApiModelProperty(name = "单次价", example = "7.00")
    String unitPrice;
    @ApiModelProperty(name = "总售价", example = "100.00")
    String price;
    @ApiModelProperty(name = "课次数", example = "15")
    Integer lessonCount;
    @ApiModelProperty(name = "单位", example = "期")
    String unitName;
    @ApiModelProperty(name = "关联数", example = "1")
    Integer linkCount;
    @ApiModelProperty(name = "可预约", example = "true")
    Boolean bookable;
    @ApiModelProperty(name = "上架状态", example = "是")
    String forSale;
    @ApiModelProperty(name = "库存", example = "100")
    Integer storage;
    @ApiModelProperty(name = "销售量", example = "0")
    Integer saleCount;
    @ApiModelProperty(name = "销售额", example = "0.00")
    Integer saleAmount;
    @ApiModelProperty(name = "销售截至", example = "2026-05-01")
    String closeDate;
    @ApiModelProperty(name = "课程状态", example = "启用")
    String state;

}
