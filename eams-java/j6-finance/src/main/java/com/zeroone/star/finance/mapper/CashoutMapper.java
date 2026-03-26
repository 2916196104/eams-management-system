package com.zeroone.star.finance.mapper;

import com.zeroone.star.finance.entity.Cashout;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dataobject.j6.finance.CashoutDO;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface CashoutMapper extends BaseMapper<CashoutDO> {
}
