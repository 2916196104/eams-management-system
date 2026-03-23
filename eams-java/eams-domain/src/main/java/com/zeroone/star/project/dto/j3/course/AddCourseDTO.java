package com.zeroone.star.project.dto.j3.course;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;

/**
 * <p>
 * 描述：添加课程数据DTO
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
@Data
@AllArgsConstructor
@ApiModel("添加课程数据DTO")
public class AddCourseDTO {
    @ApiModelProperty(value = "课程名称", example = "测试课程2")
    String name;
    @ApiModelProperty(value = "科目Id", example = "17")
    Long subjectId;
    @ApiModelProperty(value = "科目", example = "书法")
    String subjectName;
    @ApiModelProperty(value = "适用年级Id", example = "4")
    String gradeIds;
    @ApiModelProperty(value = "适用年级", example = "2026级")
    String gradeNames;
    @ApiModelProperty(value = "单位", example = "期")
    String unitName;
    @ApiModelProperty(value = "总价", example = "100.00")
    String price;
    @ApiModelProperty(value = "课次数", example = "15")
    Integer lessonCount;
    @ApiModelProperty(value = "有效月数", example = "12")
    Integer expireMonths;
    @ApiModelProperty(value = "课程类型1 大课 ,2 小班课,3 1v1", example = "1")
    Integer lessonType;
    @ApiModelProperty(value = "消课课酬", example = "0")
    String salary;
    @ApiModelProperty(value = "预约模式", example = "true")
    Boolean bookable;
    @ApiModelProperty(value = "是否上架", example = "是")
    Boolean forSale;
    @ApiModelProperty(value = "课程封面图", example = "http://localhost:80/uploads/2026-03-10/48a6d934-b1ba-43b7-84a8-5e2ac20b9fc6.jpg")
    String cover;
    @ApiModelProperty(value = "精品推荐", example = "是")
    Boolean recommend;
    @ApiModelProperty(value = "库存量", example = "100")
    Integer storage;
    @ApiModelProperty(value = "关联数", example = "1")
    Integer linkCount;
    @ApiModelProperty(value = "停售日期", example = "2026-05-01")
    String closeDate;
    @ApiModelProperty(value = "详情介绍图集", example = "http://localhost:80/uploads/2026-03-10/48a6d934-b1ba-43b7-84a8-5e2ac20b9fc6.jpg")
    String images;
    @ApiModelProperty(value = "师资说明", example = "测试师资说明")
    String teacherInfo;
    @ApiModelProperty(value = "服务说明", example = "测试服务说明")
    String serviceInfo;
}
