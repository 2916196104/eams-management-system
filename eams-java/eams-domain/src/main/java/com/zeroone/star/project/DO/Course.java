package com.zeroone.star.project.DO;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import javax.validation.constraints.NotNull;

import java.io.Serializable;

import java.util.Date;
import java.math.BigDecimal;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 课程套餐表
 * @TableName course
 */
@Data
@ApiModel(description = "课程套餐表")
@TableName("course")
public class Course implements Serializable {

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.INPUT)
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;

    /**
     * 科目id
     */
    @NotNull(message = "[科目id]不能为空")
    @ApiModelProperty("科目id")
    private Long subjectId;

    /**
     * 课程名
     */
    @NotBlank(message = "[课程名]不能为空")
    @Size(max = 50, message = "编码长度不能超过50")
    @ApiModelProperty("课程名")
    private String name;

    /**
     * 启用状态
     */
    @ApiModelProperty("启用状态")
    private Integer state;

    /**
     * 提示信息
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("提示信息")
    private String info;

    /**
     * 创建人
     */
    @ApiModelProperty("创建人")
    private Long creator;

    /**
     * 编辑者
     */
    @ApiModelProperty("编辑者")
    private Long editor;

    /**
     * 添加时间
     */
    @ApiModelProperty("添加时间")
    private Date addTime;

    /**
     * 修改时间
     */
    @ApiModelProperty("修改时间")
    private Date editTime;

    /**
     * 有效期月数
     */
    @ApiModelProperty("有效期月数")
    private Integer expireMonths;

    /**
     * 单价
     */
    @ApiModelProperty("单价")
    private BigDecimal unitPrice;

    /**
     * 总价 销售价
     */
    @ApiModelProperty("总价 销售价")
    private BigDecimal price;

    /**
     * 单位名称
     */
    @Size(max = 20, message = "编码长度不能超过20")
    @ApiModelProperty("单位名称")
    private String unitName;

    /**
     * 优惠金额 取绝对值
     */
    @ApiModelProperty("优惠金额 取绝对值")
    private BigDecimal discount;

    /**
     * 课次数
     */
    @ApiModelProperty("课次数")
    private Integer lessonCount;

    /**
     * 课堂类型1 大课  2 小班课 3 1v1
     */
    @ApiModelProperty("课堂类型1 大课  2 小班课 3 1v1")
    private Integer lessonType;

    /**
     * 描述
     */
    @ApiModelProperty("描述")
    private String description;

    /**
     * 删除标记
     */
    @ApiModelProperty("删除标记")
    private Integer deleted;

    /**
     * 是否可以预约
     */
    @ApiModelProperty("是否可以预约")
    private Integer bookable;

    /**
     * 是否上架中
     */
    @ApiModelProperty("是否上架中")
    private Integer forSale;

    /**
     * 是否推荐
     */
    @ApiModelProperty("是否推荐")
    private Integer recommend;

    /**
     * 封面
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("封面")
    private String cover;

    /**
     * 报名截止日期
     */
    @ApiModelProperty("报名截止日期")
    private Date closeDate;

    /**
     * 师资信息
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("师资信息")
    private String teacherInfo;

    /**
     * 服务说明
     */
    @Size(max = 255, message = "编码长度不能超过255")
    @ApiModelProperty("服务说明")
    private String serviceInfo;

    /**
     * 库存名额
     */
    @ApiModelProperty("库存名额")
    private Integer storage;

    /**
     * 创建者所属组织ID
     */
    @ApiModelProperty("创建者所属组织ID")
    private Long orgId;

    /**
     * 消课课酬(元/课)
     */
    @ApiModelProperty("消课课酬(元/课)")
    private BigDecimal salary;

    /**
     * 适用年级
     */
    @Size(max = 500, message = "编码长度不能超过500")
    @ApiModelProperty("适用年级")
    private String gradeIds;

    /**
     * 适用年级名
     */
    @Size(max = 500, message = "编码长度不能超过500")
    @ApiModelProperty("适用年级名")
    private String gradeNames;

}