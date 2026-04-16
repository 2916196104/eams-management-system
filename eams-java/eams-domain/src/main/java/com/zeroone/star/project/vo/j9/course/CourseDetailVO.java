package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

/**
 * 课程详情展示对象
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("课程详情")
public class CourseDetailVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "课程ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "学科ID", example = "10")
    private Long subjectId;

    @ApiModelProperty(value = "学科名称", example = "计算机科学")
    private String subjectName;

    @ApiModelProperty(value = "课程名", example = "Java入门基础课")
    private String name;

    @ApiModelProperty(value = "启用状态（0禁用 1启用），对应启/禁用操作", example = "1")
    private Integer state;

    @ApiModelProperty(value = "提示信息", example = "本课程适合零基础学员")
    private String info;

    @ApiModelProperty(value = "课程总价", example = "2999.00")
    private BigDecimal price;

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

    @ApiModelProperty(value = "上架状态（0下架 1上架），对应上架/下架操作", example = "1")
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

    @ApiModelProperty(value = "机构ID", example = "100")
    private Long orgId;

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

    @ApiModelProperty(value = "添加时间", example = "2026-01-15T10:30:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "修改时间", example = "2026-03-10T14:20:00")
    private LocalDateTime editTime;

    @ApiModelProperty("章节列表")
    private List<CourseSectionVO> sections;

    @ApiModelProperty("图片列表")
    private List<CourseImageVO> images;

    @ApiModelProperty("关联课程列表")
    private List<CourseLinkedVO> linkedCourses;
}
