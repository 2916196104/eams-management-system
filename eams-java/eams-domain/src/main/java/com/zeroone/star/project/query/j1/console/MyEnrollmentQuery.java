package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：我的报名查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("我的报名查询对象")
@Data
@EqualsAndHashCode(callSuper = true)
public class MyEnrollmentQuery extends PageQuery {

    @ApiModelProperty(value = "学员姓名或电话（模糊查询）", example = "张三")
    private String studentNameOrPhone;

    @ApiModelProperty(value = "开始日期-起始", example = "2025-03-01")
    private String startDateBegin;

    @ApiModelProperty(value = "开始日期-结束", example = "2025-03-25")
    private String startDateEnd;
}
