package com.zeroone.star.project.query.j7.operation;


import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 描述：积分记录查询对象
 */


@Data
@ApiModel("积分记录查询对象")
public class PointsRecordQuery extends PageQuery {
    @ApiModelProperty(value = "学生名称", example = "张三")
    private String name;
    @ApiModelProperty(value = "手机号", example = "136xxxxxxxx")
    private String phone;
    @ApiModelProperty(value = "变动原因", example = "课后点评奖励")
    private String reason;
    @ApiModelProperty(value = "开始时间", example = "2026-01-01 00:00:00")
    private String startTime;
    @ApiModelProperty(value = "结束时间", example = "2026-12-31 23:59:59")
    private String endTime;
}
