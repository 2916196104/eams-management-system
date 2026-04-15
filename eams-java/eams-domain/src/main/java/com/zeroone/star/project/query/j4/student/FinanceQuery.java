package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：缴欠费与退费查询对象
 * </p>
 */
@Data
public class FinanceQuery extends PageQuery {
    @ApiModelProperty(value = "业务类型（1：缴欠费 2：退费）", example = "1")
    private Integer type;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "签约记录ID", example = "2008418408985583601")
    private Long studentCourseId;

    @ApiModelProperty(value = "开始时间", example = "2026-03-01 00:00:00")
    private LocalDateTime startTime;

    @ApiModelProperty(value = "结束时间", example = "2026-03-31 23:59:59")
    private LocalDateTime endTime;

    @ApiModelProperty(value = "退款状态，仅 type=2 时生效（1：已申请 2：审核通过 3：审核驳回 4：已完成）", example = "4")
    private Integer verifyState;
}
