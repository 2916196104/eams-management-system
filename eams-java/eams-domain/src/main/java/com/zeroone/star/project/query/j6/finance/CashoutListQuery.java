package com.zeroone.star.project.query.j6.finance;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

/**
 * 请款列表查询条件
 */
@Data
@ApiModel("请款列表查询条件")
public class CashoutListQuery extends PageQuery {

    @ApiModelProperty("请款项目名（模糊查询，对应 title）")
    private String title;

    /**
     * 请款类型，对应表字段 type（tinyint）
     * 例如：1-广告宣传，2-物业费，3-办公耗材，4-水费，5-差旅费，6-其他
     */
    @ApiModelProperty("请款类型（tinyint，对应下拉：广告宣传/物业费/办公耗材/水费/差旅费/其他）")
    private Integer type;

    /**
     * 审核状态，对应表字段 verify_state（tinyint）
     * 例如：0-待审核，1-审核通过，2-已驳回
     */
    @ApiModelProperty("审核状态（tinyint：0-待审核，1-审核通过，2-已驳回）")
    private Integer verifyState;

    /**
     * 申请日期范围
     */
    @ApiModelProperty("开始日期（申请日期-起）")
    private LocalDate startDate;

    @ApiModelProperty("结束日期（申请日期-止）")
    private LocalDate endDate;

    @ApiModelProperty("申请人ID（对应 creator）")
    private Long creator;

    @ApiModelProperty("收款人姓名（模糊查询，对应 payee_name）")
    private String payeeName;
}