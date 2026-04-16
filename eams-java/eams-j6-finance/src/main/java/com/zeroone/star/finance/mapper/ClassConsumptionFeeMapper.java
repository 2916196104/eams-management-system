package com.zeroone.star.finance.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j6.finance.ClassConsumptionFeeQuery;
import com.zeroone.star.project.vo.j6.finance.ClassConsumptionFeeVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface ClassConsumptionFeeMapper {
    Page<ClassConsumptionFeeVO> queryClassConsumptionFees(Page<ClassConsumptionFeeVO> page,
                                                          @Param("condition") ClassConsumptionFeeQuery condition);
}
