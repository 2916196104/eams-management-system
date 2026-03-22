package com.zeroone.star.finance.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j6.finance.MonthlyClassFeeQuery;
import com.zeroone.star.project.vo.j6.finance.MonthlyClassFeeVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface MonthlyClassFeeMapper {
    Page<MonthlyClassFeeVO> queryMonthlyClassFees(Page<MonthlyClassFeeVO> page,
                                                  @Param("condition") MonthlyClassFeeQuery condition);
}
