package com.zeroone.star.finance.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dataobject.j6.finance.CashoutDO;
import com.zeroone.star.project.query.j6.finance.CashoutListQuery;
import com.zeroone.star.project.vo.j6.finance.CashoutDetailVO;
import com.zeroone.star.project.vo.j6.finance.CashoutListVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * 请款Mapper接口
 */
@Mapper
public interface CashoutMapper extends BaseMapper<CashoutDO> {

    /**
     * 请款列表查询（条件+分页）
     * @param page 分页参数
     * @param query 查询条件
     * @return 分页结果
     */
    Page<CashoutListVO> selectCashoutPage(Page<CashoutListVO> page, @Param("q") CashoutListQuery query);

    /**
     * 请款信息详情查询
     * @param id 请款ID
     * @return 详情VO
     */
    CashoutDetailVO selectCashoutDetailById(@Param("id") Long id);
}
