package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：我的请款查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("我的请款查询对象")
@Data
@EqualsAndHashCode(callSuper = true)
public class MyPaymentQuery extends PageQuery {

    @ApiModelProperty(value = "请款项目（模糊查询）", example = "3月教师课时费")
    private String title;

    @ApiModelProperty(value = "请款类型", example = "1")
    private Integer type;

    @ApiModelProperty(value = "申请人ID", example = "2001")
    private Long applicantId;

    @ApiModelProperty(value = "收款人（模糊查询）", example = "张老师")
    private String payeeName;
}
