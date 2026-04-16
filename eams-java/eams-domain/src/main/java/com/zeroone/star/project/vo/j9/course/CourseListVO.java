package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * 课程列表展示对象
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("课程列表项")
public class CourseListVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "课程ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "课程名", example = "Java入门基础课")
    private String name;

    @ApiModelProperty(value = "学科ID", example = "10")
    private Long subjectId;

    @ApiModelProperty(value = "学科名称", example = "计算机科学")
    private String subjectName;

    @ApiModelProperty(value = "启用状态（0禁用 1启用），对应启/禁用操作", example = "1")
    private Integer state;

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

    @ApiModelProperty(value = "封面", example = "/images/course/java.png")
    private String cover;

    @ApiModelProperty(value = "上架状态（0下架 1上架），对应上架/下架操作", example = "1")
    private Integer forSale;

    @ApiModelProperty(value = "是否可预约", example = "1")
    private Integer bookable;

    @ApiModelProperty(value = "是否推荐", example = "0")
    private Integer recommend;

    @ApiModelProperty(value = "库存名额", example = "50")
    private Integer storage;

    @ApiModelProperty(value = "添加时间", example = "2026-01-15T10:30:00")
    private LocalDateTime addTime;
}
