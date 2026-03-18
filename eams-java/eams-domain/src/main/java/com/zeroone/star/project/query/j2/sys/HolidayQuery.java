package com.zeroone.star.project.query.j2.sys;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.util.List;

/**
 * <p>
 * 描述：节日查询对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author Wind
 * @version 1.0.0
 */
@Data
@ApiModel("节日查询对象")
public class HolidayQuery extends PageQuery {
    @ApiModelProperty(value = "节日列表", example = "[2027-01-01,2027-05-26]")
    private List<LocalDate> holidayList;
}
