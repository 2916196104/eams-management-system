// com.zeroone.star.project.query.j7.console.exchange.ExchangeQuery
package com.zeroone.star.project.query.j7.operation;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 积分兑换申请列表查询参数
 * </p>
 *
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 1
 * @version 1.0.0
 */
@Data
public class ExchangeQuery extends PageQuery {

    /**
     * 礼品名称（模糊搜索）
     * 对应 UI：[礼品名称] 输入框
     * 关联表：credit_mall.name
     */
    @ApiModelProperty(value = "礼品名称（模糊搜索）", example = "笔记本")
    private String giftName;

    /**
     * 审核状态
     * 对应 UI：[审核状态] 下拉框
     * 字典值：1-待审核，2-通过，3-驳回
     * 关联表：credit_exchange.verify_state
     */
    @ApiModelProperty(value = "审核状态：1-待审核，2-通过，3-驳回", example = "1")
    private Integer verifyState;

    /**
     * 开始日期
     * 对应 UI：[开始日期] 选择器
     * 格式：yyyy-MM-dd
     * 关联表：credit_exchange.add_time
     */
    @ApiModelProperty(value = "开始日期（格式：yyyy-MM-dd）", example = "2025-09-01")
    private String startDate;

    /**
     * 结束日期
     * 对应 UI：[结束日期] 选择器
     * 格式：yyyy-MM-dd
     * 关联表：credit_exchange.add_time
     */
    @ApiModelProperty(value = "结束日期（格式：yyyy-MM-dd）", example = "2025-09-30")
    private String endDate;

    // ================= 分页参数 (对应底部翻页器) =================

    /**
     * 当前页码，默认第 1 页
     * 对应 UI：页码导航 [1]
     */
    @ApiModelProperty(value = "当前页码", example = "1")
    private Integer pageNum = 1;

    /**
     * 每页显示条数，默认 30 条
     * 对应 UI：[30 条/页]
     */
    @ApiModelProperty(value = "每页条数", example = "30")
    private long pageSize = 30;
}