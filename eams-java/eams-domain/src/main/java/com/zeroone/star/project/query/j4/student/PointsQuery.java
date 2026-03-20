package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.io.Serializable;

/**
 * PointsQuery: 回调ID、波动类型
 */
@Getter
@Setter
@ToString
@ApiModel(value = "积分查询基础对象")
public class PointsQuery extends PageQuery implements Serializable {
    @ApiModelProperty(value = "回调ID (来源记录ID)", example = "1")
    private Long callbackId;

    @ApiModelProperty(value = "波动类型 (1-增加, 2-减少)", example = "1")
    private Integer changeType;
}
