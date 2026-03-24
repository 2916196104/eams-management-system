package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j1.console.entity.CashoutDO;
import com.zeroone.star.project.dto.j1.console.MyPaymentRequestDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 请款表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface CashoutMapper extends BaseMapper<CashoutDO> {

    /**
     * 分页查询请款列表
     * @param page 分页参数
     * @param creator 申请人ID
     * @param verifyState 审核状态
     * @param startDate 开始日期
     * @param endDate 结束日期
     * @return 分页结果
     */
    IPage<MyPaymentRequestDTO> selectCashoutPage(
            Page<MyPaymentRequestDTO> page,
            @Param("creator") Long creator,
            @Param("verifyState") Integer verifyState,
            @Param("startDate") String startDate,
            @Param("endDate") String endDate
    );
}
