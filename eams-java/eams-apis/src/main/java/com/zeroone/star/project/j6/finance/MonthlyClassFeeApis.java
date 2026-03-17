package com.zeroone.star.project.j6.finance;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.MonthlyClassFeeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.MonthlyClassFeeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

/*
获取月课时费列表（条件、分页）
 */
@Api(tags = "月课时费管理")
public interface MonthlyClassFeeApis {

    /*
    获取月课时费列表（分页+条件查询）
    condition: 查询条件
     */
    @ApiOperation(value = "分页查询月课时费列表")
    JsonVO<PageDTO<MonthlyClassFeeVO>> queryPage(MonthlyClassFeeQuery condition);
}
