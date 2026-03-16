package com.zeroone.star.project.vo.j3.course;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;

/**
 * <p>
 * 描述：课程详情VO
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
@Data
@AllArgsConstructor
@ApiModel("课程详情VO")
public class CourseDetailVO {
    @ApiModelProperty(name = "课程ID", example = "2")
    Long id;
    @ApiModelProperty(name = "课程名称", example = "测试课程2")
    String name;
    @ApiModelProperty(name = "科目Id", example = "17")
    Long subjectId;
    @ApiModelProperty(name = "科目", example = "书法")
    String subjectName;
    @ApiModelProperty(name = "适用年级Id", example = "4")
    String gradeIds;
    @ApiModelProperty(name = "适用年级", example = "2026级")
    String gradeNames;
    @ApiModelProperty(name = "单位", example = "期")
    String unitName;
    @ApiModelProperty(name = "总价", example = "100.00")
    String price;
    @ApiModelProperty(name = "课次数", example = "15")
    Integer lessonCount;
    @ApiModelProperty(name = "有效月数", example = "12")
    Integer expireMonths;
    @ApiModelProperty(name = "课程类型", example = "一对一")
    String lessonType;
    @ApiModelProperty(name = "消课课酬", example = "0")
    String salary;
    @ApiModelProperty(name = "预约模式", example = "true")
    Boolean bookable;
    @ApiModelProperty(name = "是否上架", example = "是")
    Boolean forSale;
    @ApiModelProperty(name = "课程封面图", example = "http://localhost:80/uploads/2026-03-10/48a6d934-b1ba-43b7-84a8-5e2ac20b9fc6.jpg")
    String cover;
    @ApiModelProperty(name = "精品推荐", example = "是")
    Boolean recommend;
    @ApiModelProperty(name = "库存量", example = "100")
    Integer storage;
    @ApiModelProperty(name = "关联数", example = "1")
    Integer linkCount;
    @ApiModelProperty(name = "停售日期", example = "2026-05-01")
    String closeDate;
    @ApiModelProperty(name = "详情介绍图集", example = "http://localhost:80/uploads/2026-03-10/48a6d934-b1ba-43b7-84a8-5e2ac20b9fc6.jpg")
    String images;
    @ApiModelProperty(name = "师资说明", example = "测试师资说明")
    String teacher_info;
    @ApiModelProperty(name = "服务说明", example = "测试服务说明")
    String service_info;
}
