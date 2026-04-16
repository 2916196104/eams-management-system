package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 积分商城礼品表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@TableName("credit_mall")
public class CreditMall implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 所属学校
     */
    private Long schoolId;

    /**
     * 物料分类
     */
    private Long materialId;

    /**
     * 礼品分类 ID
     */
    private Long categoryId;

    /**
     * 分类名称
     */
    private String categoryName;

    /**
     * 礼品名称
     */
    private String name;

    /**
     * 兑换积分
     */
    private Integer credit;

    /**
     * 是否可以兑换
     */
    private Integer state;

    /**
     * 历史兑换数量
     */
    private Integer saleNum;

    /**
     * 预览次数
     */
    private Integer viewNum;

    /**
     * 封面
     */
    private String cover;

    /**
     * 详情内容
     */
    private String content;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;
}
