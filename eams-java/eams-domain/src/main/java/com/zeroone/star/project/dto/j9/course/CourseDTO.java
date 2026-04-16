package com.zeroone.star.project.dto.j9.course;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.hibernate.validator.constraints.Range;

import javax.validation.Valid;
import javax.validation.constraints.*;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;

@Data
public class CourseDTO {

    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "科目ID", example = "101", required = true)
    @NotNull(message = "学科ID不能为空")
    private Long subjectId;

    @ApiModelProperty(value = "课程名", example = "Java高级编程", required = true)
    @NotBlank(message = "课程名称不能为空")
    @Size(min = 1, max = 100, message = "课程名称长度必须在 1-100 个字符之间")
    private String name;

    @ApiModelProperty(value = "启用状态: 0-禁用, 1-启用", example = "1")
    @Range(min = 0, max = 1, message = "启用状态只能是 0 或 1")
    private Integer state = 1;

    @ApiModelProperty(value = "提示信息", example = "本课程包含实战项目")
    @Size(max = 500, message = "课程简介不能超过 500 个字符")
    private String info;

    @ApiModelProperty(value = "描述", example = "<p>这是一门高级Java课程</p>")
    private String description;

    @ApiModelProperty(value = "创建人ID", example = "1001")
    private Long creator;

    @ApiModelProperty(value = "编辑者ID", example = "1002")
    private Long editor;

    @ApiModelProperty(value = "有效期月数", example = "12")
    private Integer expireMonths = 12;

    @ApiModelProperty(value = "单价", example = "199.99")
    @Min(value = 0, message = "单价不能是负数")
    private BigDecimal unitPrice;

    @ApiModelProperty(value = "总价/销售价", example = "2399.00", required = true)
    @NotNull(message = "课程价格不能为空")
    @Min(value = 0, message = "课程价格不能是负数")
    @Digits(integer = 8, fraction = 2, message = "价格格式不正确，最高支持8位整数和2位小数")
    private BigDecimal price;

    @ApiModelProperty(value = "单位名称", example = "次")
    private String unitName = "次";

    @ApiModelProperty(value = "优惠金额(取绝对值)", example = "200.00")
    private BigDecimal discount;

    @ApiModelProperty(value = "课次数", example = "30")
    private Integer lessonCount;


    @ApiModelProperty(value = "课堂类型: 1-大课, 2-小班课, 3-1v1", example = "1")
    @Range(min = 1, max = 3, message = "未知的课堂类型")
    private Integer lessonType;

    @ApiModelProperty(value = "删除标记: 0-未删除, 1-已删除", example = "0")
    private Integer deleted = 0;

    @ApiModelProperty(value = "是否可以预约: 0-否, 1-是", example = "0")
    private Integer bookable = 0;


    @ApiModelProperty(value = "是否上架中: 0-否, 1-是", example = "0")
    @Range(min = 0, max = 1, message = "上架状态只能是 0 或 1")
    private Integer forSale = 0;

    @ApiModelProperty(value = "是否推荐: 0-否, 1-是", example = "0")
    private Integer recommend = 0;

    @ApiModelProperty(value = "封面图URL", example = "https://example.com/cover.jpg")
    private String cover;

    @ApiModelProperty(value = "报名截止日期", example = "2026-12-31")
    @Future(message = "报名截止日期必须是一个将来的日期")
    private LocalDate closeDate;

    @ApiModelProperty(value = "师资信息", example = "资深Java架构师，10年经验")
    private String teacherInfo;

    @ApiModelProperty(value = "服务说明", example = "提供课后辅导和答疑服务")
    private String serviceInfo;

    @ApiModelProperty(value = "库存名额", example = "50")
    private Integer storage = 0;

    @ApiModelProperty(value = "创建者所属组织ID", example = "1000")
    @Min(value = 1, message = "非法的机构ID")
    private Long orgId;

    @ApiModelProperty(value = "消课课酬(元/课)", example = "100.00")
    private BigDecimal salary;

    @ApiModelProperty(value = "适用年级ID列表(逗号分隔)", example = "1,2,3")
    private String gradeIds;

    @ApiModelProperty(value = "适用年级名列表(逗号分隔)", example = "一年级,二年级,三年级")
    private String gradeNames;

    // 关联信息
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "课程图片列表")
    @Valid
    private List<CourseImageDTO> images;

    @ApiModelProperty(value = "课程章节列表")
    @Valid
    private List<CourseSectionDTO> sections;

    @ApiModelProperty(value = "课程评价列表")
    @Valid
    private List<CourseCommentDTO> comments;

    @ApiModelProperty(value = "关联课程ID列表")
    @Valid
    private List<Long> linkedCourseIds;

    @ApiModelProperty(value = "课程体验卡列表")
    @Valid
    private List<CourseTrialDTO> trials;
}
