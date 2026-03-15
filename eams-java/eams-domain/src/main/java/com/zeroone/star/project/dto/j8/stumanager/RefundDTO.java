package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
public class RefundDTO {

    /**
     * 学生姓名
     */
    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String name;

    /**
     * 退费课程
     */
    @ApiModelProperty(value = "退费课程", example = "粤语")
    private String courseName;

    /**
     * 已收金额
     */
    @ApiModelProperty(value = "已收金额", example = "1200")
    private BigDecimal paidAmount;

    /**
     * 应退金额
     */
    @ApiModelProperty(value = "应退金额", required = true,example = "100")
    private BigDecimal dueRefundAmount;

    /**
     * 实退金额
     */
    @ApiModelProperty(value = "实退金额",required = true, example = "40")
    private BigDecimal actualRefundAmount;

    /**
     * 退课时数
     */
    @ApiModelProperty(value = "退课时数",required = true, example = "2")
    private Integer refundLessonCount;

    /**
     * 退款原因
     */
    @ApiModelProperty(value = "退款原因",required = true, example = "没时间")
    private String remark;

}
