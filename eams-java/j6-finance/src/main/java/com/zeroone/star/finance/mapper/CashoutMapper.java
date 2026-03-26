package com.zeroone.star.finance.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.plugins.pagination.PageDTO;
import com.zeroone.star.finance.entity.Cashout;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dataobject.j6.finance.CashoutDO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface CashoutMapper extends BaseMapper<CashoutDO> {
    /**
     * 请款列表查询（条件+分页）
     */
    Page<CashoutListVO> selectCashoutPage(Page<CashoutListVO> page, @Param("q") CashoutListQuery query);

    /**
     * 请款信息详情查询
     */
    CashoutDetailVO selectCashoutDetailById(@Param("id") Long id);
}
