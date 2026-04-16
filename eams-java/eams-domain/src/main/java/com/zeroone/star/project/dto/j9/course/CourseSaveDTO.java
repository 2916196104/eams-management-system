package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import javax.validation.Valid;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;

/**
 * 课程保存传输对象（新增/更新）
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("课程保存数据")
public class CourseSaveDTO implements Serializable {

    private static final long serialVersionUID = 1L;


    @ApiModelProperty(value = "课程ID（为空时新增，非空时更新）", example = "1")
    private Long id;

    @NotNull(message = "学科ID不能为空")
    @ApiModelProperty(value = "学科ID", required = true, example = "10")
    private Long subjectId;

    @NotBlank(message = "课程名称不能为空")
    @ApiModelProperty(value = "课程名", required = true, example = "Java入门基础课")
    private String name;

    @ApiModelProperty(value = "启用状态", example = "1")
    private Integer state;

    @ApiModelProperty(value = "提示信息", example = "本课程适合零基础学员")
    private String info;

    @NotNull(message = "课程总价不能为空")
    @Min(value = 0, message = "课程价格不能是负数")
    @ApiModelProperty(value = "课程总价", example = "2999.00")
    private BigDecimal price;

    @Min(value = 0, message = "单价不能是负数")
    @ApiModelProperty(value = "课时单价", example = "99.97")
    private BigDecimal unitPrice;

    @ApiModelProperty(value = "优惠金额", example = "200.00")
    private BigDecimal discount;

    @ApiModelProperty(value = "课次数", example = "30")
    private Integer lessonCount;

    @ApiModelProperty(value = "课堂类型", example = "2")
    private Integer lessonType;

    @ApiModelProperty(value = "描述", example = "全面讲解Java语言基础语法与面向对象编程")
    private String description;

    @ApiModelProperty(value = "是否可预约", example = "1")
    private Integer bookable;

    @ApiModelProperty(value = "是否上架中", example = "1")
    private Integer forSale;

    @ApiModelProperty(value = "是否推荐", example = "0")
    private Integer recommend;

    @ApiModelProperty(value = "封面", example = "/images/course/java.png")
    private String cover;

    @ApiModelProperty(value = "报名截止日期", example = "2026-06-30")
    private LocalDate closeDate;

    @ApiModelProperty(value = "师资信息", example = "资深Java讲师，10年教学经验")
    private String teacherInfo;

    @ApiModelProperty(value = "服务说明", example = "提供课后答疑、作业批改服务")
    private String serviceInfo;

    @ApiModelProperty(value = "库存名额", example = "50")
    private Integer storage;

    @ApiModelProperty(value = "消课课酬", example = "80.00")
    private BigDecimal salary;

    @ApiModelProperty(value = "适用年级ID", example = "1,2,3")
    private String gradeIds;

    @ApiModelProperty(value = "适用年级名", example = "一年级,二年级,三年级")
    private String gradeNames;

    @ApiModelProperty(value = "有效期月数", example = "12")
    private Integer expireMonths;

    @ApiModelProperty(value = "课时单位名称", example = "课时")
    private String unitName;

    @ApiModelProperty("章节列表")
    @Valid
    private List<CourseSectionDTO> sections;

    @ApiModelProperty("图片列表")
    @Valid
    private List<CourseImageDTO> images;

    @ApiModelProperty(value = "关联课程ID列表", example = "[2, 3]")
    private List<Long> linkedCourseIds;
}
