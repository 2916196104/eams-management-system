package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：我的客户查询对象
 * </p>
 * @author hxb
 */
@Data
@ApiModel(value = "我的客户查询对象")
@EqualsAndHashCode(callSuper = true)
public class MyCustomerQuery extends PageQuery {

    @ApiModelProperty(value = "学员姓名（模糊查询）")
    private String studentName;

    @ApiModelProperty(value = "联系电话")
    private String contactPhone;

    @ApiModelProperty(value = "学习阶段：0-意向学员 1-在读学员 2-结业学员")
    private Integer stage;

    @ApiModelProperty(value = "性别：0-未知 1-男 2-女")
    private Integer gender;

    @ApiModelProperty(value = "开始日期（添加时间）")
    private String startDate;

    @ApiModelProperty(value = "结束日期（添加时间）")
    private String endDate;
}
