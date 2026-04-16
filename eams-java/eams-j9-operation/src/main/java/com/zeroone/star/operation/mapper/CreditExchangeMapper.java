package com.zeroone.star.operation.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.operation.entity.CreditExchangeDO;
import com.zeroone.star.project.query.j9.operation.CreditExchangeQuery;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * 积分商城兑换记录 Mapper 接口
 */
@Mapper
public interface CreditExchangeMapper extends BaseMapper<CreditExchangeDO> {

    /**
     * 分页查询兑换申请列表（包含关联名称）
     * @param page 分页参数
     * @param condition 查询条件
     * @return 分页列表
     */
    Page<CreditExchangeVO> selectCreditExchangePage(Page<CreditExchangeVO> page, @Param("condition") CreditExchangeQuery condition);
}
