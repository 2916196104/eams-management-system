package com.zeroone.star.finance.mapper;

import com.zeroone.star.project.vo.j6.finance.FinanceRecordVo;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface FundManageMapper {

    List<FinanceRecordVo> findAll();

}
