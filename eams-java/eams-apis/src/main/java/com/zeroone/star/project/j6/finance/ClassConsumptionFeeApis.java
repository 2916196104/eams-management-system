package com.zeroone.star.project.j6.finance;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.ClassConsumptionFeeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.ClassConsumptionFeeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

/**
 * 消课课酬Api
 */
@Api(tags = "消课课酬管理")
public interface ClassConsumptionFeeApis {

    @ApiOperation(value = "分页查询消课课酬列表")
    JsonVO<PageDTO<ClassConsumptionFeeVO>> queryPage(ClassConsumptionFeeQuery condition);
}
