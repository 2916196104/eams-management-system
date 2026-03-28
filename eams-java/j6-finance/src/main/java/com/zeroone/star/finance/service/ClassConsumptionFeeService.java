package com.zeroone.star.finance.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.ClassConsumptionFeeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.ClassConsumptionFeeVO;

public interface ClassConsumptionFeeService {
    public JsonVO<PageDTO<ClassConsumptionFeeVO>> listClassConsumptionFees(ClassConsumptionFeeQuery query);
}
