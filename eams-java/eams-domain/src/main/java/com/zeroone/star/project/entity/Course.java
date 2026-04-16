package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 课程套餐表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("course")
public class Course implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 科目 id
     */
    private Long subjectId;

    /**
     * 课程名
     */
    private String name;

    /**
     * 启用状态
     */
    private Integer state;

    /**
     * 提示信息
     */
    private String info;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑者
     */
    private Long editor;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 修改时间
     */
    private LocalDateTime editTime;

    /**
     * 有效期月数
     */
    private Integer expireMonths;

    /**
     * 单价
     */
    private BigDecimal unitPrice;

    /**
     * 总价 销售价
     */
    private BigDecimal price;

    /**
     * 单位名称
     */
    private String unitName;

    /**
     * 优惠金额 取绝对值
     */
    private BigDecimal discount;

    /**
     * 课次数
     */
    private Integer lessonCount;

    /**
     * 课堂类型 1 大课  2 小班课 3 1v1
     */
    private Integer lessonType;

    /**
     * 描述
     */
    private String description;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 是否可以预约
     */
    private Integer bookable;

    /**
     * 是否上架中
     */
    private Integer forSale;

    /**
     * 是否推荐
     */
    private Integer recommend;

    /**
     * 封面
     */
    private String cover;

    /**
     * 报名截止日期
     */
    private LocalDate closeDate;

    /**
     * 师资信息
     */
    private String teacherInfo;

    /**
     * 服务说明
     */
    private String serviceInfo;

    /**
     * 库存名额
     */
    private Integer storage;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;

    /**
     * 消课课酬 (元/课)
     */
    private BigDecimal salary;

    /**
     * 适用年级
     */
    private String gradeIds;

    /**
     * 适用年级名
     */
    private String gradeNames;
}
