package com.zeroone.star.project.query.j2.sys;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

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
// ... existing code ...
// ... existing code ...
@Data
@ApiModel("节日查询对象")
public class HolidayQuery extends PageQuery {
    @ApiModelProperty(value = "节日年份列表", example = "[2025, 2026]")
    private List<Integer> holidayList;
}



