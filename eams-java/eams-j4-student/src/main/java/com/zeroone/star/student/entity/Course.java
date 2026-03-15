package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.FieldFill;
import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 课程套餐表
 * </p>
 *
 * @author erji
 * @since 2026-03-15
 */
@Getter
@Setter
public class Course implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 科目id
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
    @TableField(fill = FieldFill.INSERT)
    private Long creator;

    /**
     * 编辑者
     */
    @TableField(fill = FieldFill.INSERT)
    private Long editor;

    /**
     * 添加时间
     */
    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 修改时间
     */
    @TableField(fill = FieldFill.INSERT)
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
     * 课堂类型1 大课  2 小班课 3 1v1
     */
    private Integer lessonType;

    /**
     * 描述
     */
    private String description;

    /**
     * 删除标记
     */
    private Boolean deleted;

    /**
     * 是否可以预约
     */
    private Boolean bookable;

    /**
     * 是否上架中
     */
    private Boolean forSale;

    /**
     * 是否推荐
     */
    private Boolean recommend;

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
     * 创建者所属组织ID
     */
    private Long orgId;

    /**
     * 消课课酬(元/课)
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
