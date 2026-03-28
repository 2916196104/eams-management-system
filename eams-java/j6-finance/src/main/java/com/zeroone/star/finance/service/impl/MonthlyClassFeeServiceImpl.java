package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.finance.mapper.MonthlyClassFeeMapper;
import com.zeroone.star.finance.service.MonthlyClassFeeService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.MonthlyClassFeeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.MonthlyClassFeeVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class MonthlyClassFeeServiceImpl implements MonthlyClassFeeService {

    @Autowired
    private MonthlyClassFeeMapper monthlyClassFeeMapper;

    @Override
    public JsonVO<PageDTO<MonthlyClassFeeVO>> listMonthlyClassFees(MonthlyClassFeeQuery condition) {
        Page<MonthlyClassFeeVO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        Page<MonthlyClassFeeVO> resultPage = monthlyClassFeeMapper.queryMonthlyClassFees(page, condition);
        return JsonVO.success(PageDTO.create(resultPage));
    }
}
