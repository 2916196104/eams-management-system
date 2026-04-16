// com.zeroone.star.project.dto.j7.operation.ExchangeDTO
package com.zeroone.star.project.dto.j7.operation;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

/**
 * <p>
 * 积分兑换申请审核操作数据传输对象
 * 对应 UI：[请审核] 弹窗表单
 * </p>
 *
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 *
 * @author 1
 * @version 1.0.0
 */
@Data
public class ExchangeDTO {

    /**
     * 兑换记录 ID
     * 对应逻辑：前端表格勾选的行 ID，或弹窗打开时携带的 ID
     * 必填项：必须指定要审核哪一条记录
     * 关联表：credit_exchange.id
     */
    @NotNull(message = "兑换记录 ID 不能为空")
    @ApiModelProperty(value = "兑换记录 ID (必填)", required = true, example = "1")
    private Long id;

    /**
     * 审核结果
     * 对应 UI：[审核状态] 单选框 (通过 / 驳回)
     * 字典值：2-通过，3-驳回
     * 必填项：必须选择一个结果
     * 关联表：credit_exchange.verify_state
     */
    @NotNull(message = "审核结果不能为空")
    @ApiModelProperty(value = "审核结果：2-通过，3-驳回 (必填)", required = true, example = "2")
    private Integer auditResult;

    /**
     * 审核说明
     * 对应 UI：[审核说明] 文本域
     * 选填项：驳回时建议必填，通过时可选
     * 关联表：credit_exchange.verify_remark
     */
    @ApiModelProperty(value = "审核说明 (可选，驳回时建议填写)", example = "材料齐全，予以通过")
    private String remark;
}