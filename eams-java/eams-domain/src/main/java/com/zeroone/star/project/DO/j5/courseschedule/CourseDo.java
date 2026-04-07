package com.zeroone.star.project.DO.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel(description = "课程DO")
public class CourseDo {
    @ApiModelProperty(value = "ID")
    private Long id;
    @ApiModelProperty(value = "科目ID")
    private Long subjectId;
    @ApiModelProperty(value = "课程名称")
    private String name;
    @ApiModelProperty(value = "状态")
    private Integer state;
    @ApiModelProperty(value = "简介")
    private String info;
    @ApiModelProperty(value = "创建人")
    private Long creator;
    @ApiModelProperty(value = "编辑人")
    private Long editor;
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;
    @ApiModelProperty(value = "编辑时间")
    private LocalDateTime editTime;
    @ApiModelProperty(value = "过期月数")
    private Integer expireMonths;
    @ApiModelProperty(value = "单价")
    private BigDecimal unitPrice;
    @ApiModelProperty(value = "总价")
    private BigDecimal price;
    @ApiModelProperty(value = "单位名称")
    private String unitName;
    @ApiModelProperty(value = "折扣")
    private BigDecimal discount;
    @ApiModelProperty(value = "课次数")
    private Integer lessonCount;
    @ApiModelProperty(value = "课程类型")
    private Integer lessonType;
    @ApiModelProperty(value = "描述")
    private String description;
    @ApiModelProperty(value = "删除标记")
    private Integer deleted;
    @ApiModelProperty(value = "是否可预约")
    private Integer bookable;
    @ApiModelProperty(value = "是否售卖")
    private Integer forSale;
    @ApiModelProperty(value = "是否推荐")
    private Integer recommend;
    @ApiModelProperty(value = "封面")
    private String cover;
    @ApiModelProperty(value = "关闭日期")
    private LocalDate closeDate;
    @ApiModelProperty(value = "教师信息")
    private String teacherInfo;
    @ApiModelProperty(value = "服务信息")
    private String serviceInfo;
    @ApiModelProperty(value = "库存")
    private Integer storage;
    @ApiModelProperty(value = "机构ID")
    private Long orgId;
    @ApiModelProperty(value = "课时费")
    private BigDecimal salary;
    @ApiModelProperty(value = "年级ID串")
    private String gradeIds;
    @ApiModelProperty(value = "年级名称串")
    private String gradeNames;
}
